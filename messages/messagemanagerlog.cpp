#include "messagemanagerlog.h"
#include "ui_messagemanagerlog.h"

MessageManagerLog::MessageManagerLog(QLayout *layout) :
    QWidget(0),
    ui(new Ui::MessageManagerLog) {
    ui->setupUi(this);
    logEnable = false;
    if(layout)
        layout->addWidget(this);

    ui->splitter->setSizes(QList<int>() << height() * 0.7 << height() * 0.3);
}

MessageManagerLog::~MessageManagerLog() {
    delete ui;
}

void MessageManagerLog::logSend(const MessageLog &log, QStringList*) {
    if(logEnable)
        ui->logSend->appendPlainText(Transport::timeLocalStr + " : " + log.getVerboseMessage());
}
void MessageManagerLog::logReceive(const MessageLog &log, QStringList*) {
    if(logEnable)
        ui->logReceive->appendPlainText(Transport::timeLocalStr + " : " + log.getVerboseMessage());
}

void MessageManagerLog::action() {
    if(sender() == ui->logSendCopy)
        QApplication::clipboard()->setText(ui->logSend->toPlainText());
    else if(sender() == ui->logReceiveCopy)
        QApplication::clipboard()->setText(ui->logReceive->toPlainText());
}
