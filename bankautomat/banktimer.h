#ifndef BANKTIMER_H
#define BANKTIMER_H

#include <QObject>
#include <QDebug>
#include <QTimer>




enum states
{
    tier0,                  // tässä tilakoneen tilat, nimetty sen mukaan,
    tier1,                  // millä kirjautumisasteella ne vaikuttavat.
    tier2,                  // tier0 on pohjataso, tier1 on login-tila,
    tier3,                  // tier2 bankmain ja tier3 bankactions ja nostoruudut.
                            //  Tällä tavoin voidaan hallita mihin ruutuun palataan,
                            // kun ajastin laukeaa, ja paljonko aikaa ajastimeen
                            // säädetään.
};
enum events
{
    standBy,              // kun aloitetaan login käytetään tätä.
    moveTier,               // kun tasojen välillä liikutaan.
    timeReset,              // tällä resetataan aika, ei välttämättä ole tarpeellinen...
    timeStart,              // tällä käynnistetään ajastin.
    timerExpires,           // käsitellään välivaiheella ajan loppuminen.
    outOfTime               // tässä aika loppuu.
};

class bankTimer : public QObject
{
    Q_OBJECT
public:
    explicit bankTimer(QObject *parent = nullptr);
    ~bankTimer();

public slots:
    void runStateMachine(states,events);
    void handleTimeout();
    void timerProgress();

signals:
    void timeReset_signal(states,events);
    void timeStart_signal(states,events);
    void outOfTime_signal(states,events);
    void timeout_signal();

private slots:
    void on_timeReset_clicked();

private:
    states State;
    events Event;
    QTimer timer;
    QTimer timer2;
    bankTimer * pBankTimer;

    void timesUpHandler(events e);
    void tier0Handler(events e);
    void tier1Handler(events e);
    void tier2Handler(events e);
    void tier3Handler(events e);
};

#endif // BANKTIMER_H
