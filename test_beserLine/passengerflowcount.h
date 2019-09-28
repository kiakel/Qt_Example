#ifndef PASSENGERFLOWCOUNT_H
#define PASSENGERFLOWCOUNT_H

#include <QObject>
#include <QTimer>
#include <QVariantMap>

#define PASSENGERFLOWCOUNT_REGISTERTYPE \
    qmlRegisterType< PassengerFlowCount >( "PassengerFlowCount", 1, 0, "PassengerFlowCount" )

class PassengerFlowCount : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap sexMap MEMBER m_sexMap CONSTANT/*NOTIFY sexMapChanged*/)
    Q_PROPERTY(QVariantMap ageMap MEMBER m_ageMap CONSTANT/*NOTIFY ageMapChanged*/)
    Q_PROPERTY(int maleCt MEMBER m_maleCt CONSTANT/*NOTIFY maleCtChanged*/)
    Q_PROPERTY(int femaleCt MEMBER m_femaleCt CONSTANT/*NOTIFY femaleCtChanged*/)
    Q_PROPERTY(QVariant ageCountMap  MEMBER m_ageCountMap CONSTANT)

public:
    explicit PassengerFlowCount(QObject *parent = nullptr);
    ~PassengerFlowCount() override;

signals:
    void dataChanged();

public slots:
    /**
     *\brief 开启定时器，初始化数据库
     */
    bool initEnvironment();

private slots:
    void selectPassengerFlow();

private:
    QVariantMap m_sexMap; //!< 每个小时性别统计信息               数据形式 "10",{"female":12},{"male":23}
    QVariantMap m_ageMap; //!< 每个小时某个性别的年龄阶段统计     数据形式 "10",{"female_20":12},{"female_40":11},{"female_60":2},{"female_100":0}
    QVariantMap m_ageCountMap; //!< 当天每个年龄阶段的人数
    QTimer m_timer; //!< 测试数据
    int m_maleCt{0}; //!< 当天客流量男士总人数
    int m_femaleCt{0}; //!< 当天客流量女士总人数


};

#endif // PASSENGERFLOWCOUNT_H
