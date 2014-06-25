//====================================================================================
//
// Belenus Kliens alkalmazas (c) Pagony Multimedia Studio Bt - 2014
//
//====================================================================================
//
// Filename    : gibbig.h
// AppVersion  : 1.0
// FileVersion : 1.0
// Author      : Bikfalvi Tamas
//
//====================================================================================
// Gibbig rendszerrel kapcsolatos reszek implementalasa
//====================================================================================

#ifndef GIBBIG_H
#define GIBBIG_H

//====================================================================================

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

//====================================================================================
class cGibbigAction
{
public:
    enum teGibbigAction
    {
        GA_DEFAULT = 0,
        GA_AUTHENTICATE,
        GA_PCREGISTER,
        GA_PCUSE
    };

    static const char *toStr( teGibbigAction p_enGA )
    {
        switch( p_enGA )
        {
            case GA_DEFAULT:        return "Unidentified";    break;
            case GA_AUTHENTICATE:   return "Authenticate";   break;
            case GA_PCREGISTER:     return "Registration"; break;
            case GA_PCUSE:          return "CardUsage";    break;
            default:                return "INVALID";
        }
    }
};


class cGibbig : public QObject
{
    Q_OBJECT

public:

    cGibbig();
    ~cGibbig();

    void    setHost( const QString p_qsHost );
    void    setPort( const QString p_qsPort );
    void    setUserName( const QString p_qsUserName );
    void    setPassword( const QString p_qsPassword );
    void    setTimeout( const int p_inTimeout );

    void    gibbigAuthenticate();
    void    gibbigSendPatientCard( QString p_qsBarcode );

    void    gibbigClearError()          {   m_bErrorOccured = false;    }
    bool    gibbigIsErrorOccured()      {   return m_bErrorOccured;     }

    QString gibbigErrorStr()            {   return m_qsError;           }

protected:

    void    timerEvent( QTimerEvent *p_poEvent );

protected slots:

    void    slotRestRequestFinished(QNetworkReply *p_gbReply);

signals:

    void    signalErrorOccured();

private:

    QNetworkAccessManager           *m_gbRestManager;
    QNetworkRequest                  m_gbRequest;

    QString                          m_qsHost;
    QString                          m_qsPort;
    QString                          m_qsGbUserName;
    QString                          m_qsGbPassword;
    int                              m_inTimeout;

    QString                          m_qsMessage;
    QString                          m_qsError;
    int                              m_inTimer;

    QString                          m_qsToken;

    bool                             m_bErrorOccured;
    bool                             m_bAuthenticationInProgress;

    cGibbigAction::teGibbigAction    m_teGibbigAction;

    void                            _processMessage();

};
//====================================================================================

#endif // GIBBIG_H
