#include "banktimer.h"
#include "QDebug"
#include "QTimer"
#include <QObject>
#include "ui_login.h"




bankTimer::bankTimer(QObject *parent)
    : QObject{parent}
{
    connect(this,SIGNAL(timeReset_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(this,SIGNAL(timeStart_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(this,SIGNAL(outOfTime_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(&this->timer,SIGNAL(timeout()),
            this,SLOT(handleTimeout()));

    connect(&this->timer2,SIGNAL(timeout()),
            this,SLOT(timerProgress()));



    State = tier0;
    Event = standBy;
    timer2.start(1000);

    runStateMachine(State,Event);

}

bankTimer::~bankTimer()
{


}



void bankTimer::runStateMachine(states s, events e)
{
    switch (s) {

        case tier0:
            tier0Handler(e);
        break;

        case tier1:
            tier1Handler(e);
        break;

        case tier2:
            tier2Handler(e);
        break;

        case tier3:
            tier3Handler(e);
        break;

        default:
            qDebug()<<"State = "<<State<<" and event = "<< e;

    }

}

void bankTimer::handleTimeout()
{
    if(State == tier1)
    {
        State = tier1;
        Event = timerExpires;
    }
    else if(State == tier2)
    {
        State = tier1;
        Event = timerExpires;
    }
    else if(State == tier3)
    {
        State = tier1;
        Event = timerExpires;
    }
    else
    {
        qDebug()<<"...Error In Handling Timeout...";
    }

    runStateMachine(State,Event);
}

void bankTimer::tier0Handler(events e)
{
    if(e == standBy)
    {

        qDebug()<<"...System Standing By...";


    }
    else if(e == timeStart)
    {
        qDebug()<<"...Initializing Login...";
        State = tier1;
        Event = timeStart;
        emit timeStart_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }

}

void bankTimer::tier1Handler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting Timer...";
        timer.start(10000);
    }
    else if(e == timeReset)
    {
        qDebug()<<"...User Activity detected On T-1...";
        timer.stop();
        State = tier1;
        Event = timeStart;
        emit timeReset_signal(State,Event);
    }
    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping To T-0";
        State = tier0;
        Event = standBy;
        emit outOfTime_signal(State,Event);
        emit timeout_signal();
    }
    else if(e == moveTier)
    {
        timer.stop();
        qDebug()<<"...User Moving On To T-2...";
        State = tier2;
        Event = timeStart;
        emit outOfTime_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }

}

void bankTimer::tier2Handler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting timer...";
        timer.start(10000);
    }
    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping to T-1...";
        State = tier1;
        Event = timeStart;
        emit outOfTime_signal(State,Event);
    }
    else if(e == moveTier)
    {
        timer.stop();
        qDebug()<<"...User Moving On To T-3...";
        State = tier3;
        Event = timeStart;
        emit outOfTime_signal(State,Event);
    }
    else if(e == standBy)
    {
        timer.stop();
        qDebug()<<"...Initializing Logout...";
        State = tier0;
        Event = standBy;
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }

}

void bankTimer::tier3Handler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting Timer...";
        timer.start(10000);
    }
    else if(e == timeReset)
    {
        qDebug()<<"...User Activity Detected On T-3...";
        timer.stop();
        State = tier3;
        Event = timeStart;
        emit timeReset_signal(State,Event);
    }
    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping To T-2...";
        State = tier2;
        Event = timeStart;
        emit outOfTime_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }

}

void bankTimer::timerProgress()
{
   // ui->progressBar->setValue(timer.remainingTime()/1000+1);
    qDebug()<<timer.remainingTime()/1000;

}



/******************************************
   Click Handlers
******************************************/



void bankTimer::on_timeReset_clicked()
{
    // State can be either timesOn or timesUp
    Event = timeReset;
    runStateMachine(State,Event);
}

