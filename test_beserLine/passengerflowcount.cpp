#include "passengerflowcount.h"

#include <iostream>
#include <ctime>

#include <QDateTime>
#include <QThread>
#include <QDebug>

PassengerFlowCount::PassengerFlowCount(QObject *parent) : QObject(parent)
{
    m_timer.setInterval(1000 * 60 * 1);
    connect(&m_timer, &QTimer::timeout, this, &PassengerFlowCount::selectPassengerFlow);
}

PassengerFlowCount::~PassengerFlowCount()
{

}

bool PassengerFlowCount::initEnvironment()
{
    // 初始化数据库
    m_timer.start();
    selectPassengerFlow();
    return true;
}

void PassengerFlowCount::selectPassengerFlow()
{
    QDateTime currentTime = QDateTime::currentDateTime();

    if (currentTime.time().hour() < 10 || currentTime.time().hour() >= 22){
        m_sexMap.clear();
        m_ageMap.clear();
        m_ageCountMap.clear();
        m_femaleCt=0;
        m_maleCt=0;
        return;
    }

    QString currentHour=QString::number(currentTime.time().hour());

    // 测试数据
    unsigned int seed = static_cast<unsigned int>(QDateTime::currentMSecsSinceEpoch());
    std::srand(seed);
    // 总计进入人数
    int humanCt = std::rand()%50+1;
    float percent = std::rand()%(100+1)/100.0f;

    auto&& oneHourSexMap = m_sexMap.value(currentHour).toMap();
    int female = static_cast<int>(std::ceilf(humanCt * percent));
    int male = static_cast<int>(std::floorf(humanCt * (1-percent) ));
    oneHourSexMap.insert("female", oneHourSexMap.value("female").toInt()+female);
    oneHourSexMap.insert("male", oneHourSexMap.value("male").toInt()+male);
    m_sexMap.insert(currentHour, oneHourSexMap);

    m_femaleCt += female;
    m_maleCt += male;

    //age
    QStringList ageArray{"20","40","60","100"};
    int tmpHumanCt = humanCt;
    while (humanCt > 0){
        seed = static_cast<unsigned int>(QDateTime::currentMSecsSinceEpoch());
        std::srand(seed);
        int arrIndex = std::rand() % ageArray.length();
        percent = std::rand()%(100+1)/100.0f;
        auto&& oneHourAgeMap = m_ageMap.value(currentHour).toMap();
        int oneAgeRangeValue = oneHourAgeMap.value(ageArray.at(arrIndex)).toInt();
        oneHourAgeMap.insert(ageArray.at(arrIndex), static_cast<int>(std::ceilf(humanCt*percent) + oneAgeRangeValue));
        m_ageCountMap.insert(ageArray.at(arrIndex), m_ageCountMap.value(ageArray.at(arrIndex)).toInt()
                                                         + oneHourAgeMap.value(ageArray.at(arrIndex)).toInt());
        m_ageMap.insert(currentHour, oneHourAgeMap);

        humanCt -= oneHourAgeMap.value(ageArray.at(arrIndex)).toInt();
        QThread::usleep(1);
    }

    qInfo()<<tmpHumanCt<<","<<m_ageCountMap["20"].toInt()<<","<<m_ageCountMap["40"].toInt()<<","<<
        m_ageCountMap["60"].toInt()<<","<<m_ageCountMap["100"].toInt();

    emit dataChanged();
}
