#include "timeserver.h"
#include "timethread.h"
#include "dialog.h"

TimeServer::TimeServer(QObject *parent) : QTcpServer (parent)
{
    dlg = (Dialog *) parent;
}

void TimeServer::incomingConnection(int socketDescriptor)
{
    TimeThread *thread = new TimeThread(socketDescriptor);

    connect (thread, &QThread::finished, dlg, &Dialog::slotShow, Qt::QueuedConnection);
    connect (thread, &QThread::finished, thread, &TimeThread::deleteLater, Qt::DirectConnection);

    thread->start ();
}
