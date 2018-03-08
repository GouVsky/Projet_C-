#include "databasecommunicator.h"

DataBaseCommunicator::DataBaseCommunicator(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::database("QSQLITE");

    db.open();
}

DataBaseCommunicator::~DataBaseCommunicator()
{
    db.close();
}

bool DataBaseCommunicator::checkLoginPassword(const QString &login, const QString &password)
{
    bool correctLoginPassword = false;

    QSqlQuery query(db);

    query.exec("SELECT Login, MdP FROM TCompte;");

    while (query.next())
    {
        if (query.value(0).toString().toStdString() == login.toStdString()
            && query.value(1).toString().toStdString() == password.toStdString())
        {
            correctLoginPassword = true;
        }
    }

    return correctLoginPassword;
}

 bool DataBaseCommunicator::addClientToDatabase(Ui::AddingClient * ui)
 {
         QSqlQuery query(db);
         query.prepare("INSERT INTO TClient(Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateRdv, DureeRdv, Priorite) VALUES "
                              "(:NomAdd, :PrenomAdd, :AdresseAdd, :VilleAdd, :CPAdd, :CommentaireAdd, :TelAdd, :DateRdvAdd, :DureeRdvAdd, :PrioriteAdd)");
         query.bindValue(":NomAdd", ui->editName->text());
         query.bindValue(":PrenomAdd", ui->editFirstName->text());
         query.bindValue(":AdresseAdd", ui->editAddress->text());
         query.bindValue(":VilleAdd", ui->editCity->text());
         query.bindValue(":CPAdd", ui->editPostalCode->text());
         query.bindValue(":CommentaireAdd", ui->editComments->toPlainText());
         query.bindValue(":TelAdd", ui->editPhoneNumber->text().toInt());
         query.bindValue(":DateRdvAdd", ui->editDate->text());
         query.bindValue(":DureeRdvAdd", ui->editConsultingTime->text());
         query.bindValue(":PrioriteAdd", ui->priorityList->itemData(ui->priorityList->currentIndex()));
         if(!query.exec())
         {
             qDebug() << db.lastError().text();
             qDebug() << "Erreur à l'insersion de donnees client !\n";
         }
     else
     {
         qDebug() << db.lastError().text();
         qDebug() << "Erreur à louverture de la base !\n";
     }
 }
