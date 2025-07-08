#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QKeySequence>
#include <QPlainTextEdit>
#include <QToolButton>
#include <QTabWidget>

#include "../modules/Manager/Manager.hpp"
#include "../modules/HelpFunction.hpp"
#include "../modules/Validator.hpp"


class AddPetDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddPetDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Добавить нового питомца");
        petNameEdit = new QLineEdit(this);
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        petTypeEdit = new QLineEdit(this);
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        formLayout->addRow("Вид питомца:", petTypeEdit);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
    }
    ~AddPetDialog() {}
    QString petName() const { return petNameEdit->text(); }
    QString ownerFio() const { return ownerFioEdit->text(); }
    QString petType() const { return petTypeEdit->text(); }
private:
    QLineEdit *petNameEdit;
    QLineEdit *ownerFioEdit;
    QLineEdit *petTypeEdit;
};


class AddVisitDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddVisitDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Добавить новый визит");
        petNameEdit = new QLineEdit(this);
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        diagnoseEdit = new QLineEdit(this);
        doctorFioEdit = new QLineEdit(this);
        dataEdit = new QLineEdit(this);
        dataEdit->setPlaceholderText("День Месяц Год (например, 15 май 2023)");
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        formLayout->addRow("Диагноз: ", diagnoseEdit);
        formLayout->addRow("ФИО доктора:", doctorFioEdit);
        formLayout->addRow("Дата консультации:", dataEdit);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
    }
    ~AddVisitDialog() {}
    QString petName() const { return petNameEdit->text(); }
    QString ownerFio() const { return ownerFioEdit->text(); }
    QString diagnosStr() const { return diagnoseEdit->text(); }
    QString doctorStr() const { return doctorFioEdit->text(); }
    QString timeStr() const { return dataEdit->text(); }
private:
    QLineEdit *petNameEdit;
    QLineEdit *ownerFioEdit;
    QLineEdit *diagnoseEdit;
    QLineEdit *doctorFioEdit;
    QLineEdit *dataEdit;
};

class RemovePetDialog : public QDialog {
    Q_OBJECT
public:
    explicit RemovePetDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Удалить питомца");
        petNameEdit = new QLineEdit(this);
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        petTypeEdit = new QLineEdit(this);
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        formLayout->addRow("Вид питомца:", petTypeEdit);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
    }
    ~RemovePetDialog() {}
    QString petName() const { return petNameEdit->text(); }
    QString ownerFio() const { return ownerFioEdit->text(); }
    QString petType() const { return petTypeEdit->text(); }
private:
    QLineEdit *petNameEdit;
    QLineEdit *ownerFioEdit;
    QLineEdit *petTypeEdit;
};

class RemoveVisitDialog : public QDialog {
    Q_OBJECT
public:
    explicit RemoveVisitDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Удалить визит");
        petNameEdit = new QLineEdit(this);
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        diagnoseEdit = new QLineEdit(this);
        doctorFioEdit = new QLineEdit(this);
        dataEdit = new QLineEdit(this);
        dataEdit->setPlaceholderText("День Месяц Год (например, 15 май 2023)");
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        formLayout->addRow("Диагноз: ", diagnoseEdit);
        formLayout->addRow("ФИО доктора:", doctorFioEdit);
        formLayout->addRow("Дата консультации:", dataEdit);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
    }
    ~RemoveVisitDialog() {}
    QString petName() const { return petNameEdit->text(); }
    QString ownerFio() const { return ownerFioEdit->text(); }
    QString diagnosStr() const { return diagnoseEdit->text(); }
    QString doctorStr() const { return doctorFioEdit->text(); }
    QString timeStr() const { return dataEdit->text(); }
private:
    QLineEdit *petNameEdit;
    QLineEdit *ownerFioEdit;
    QLineEdit *diagnoseEdit;
    QLineEdit *doctorFioEdit;
    QLineEdit *dataEdit;
};

class DebugWindow : public QDialog  {
    Q_OBJECT
public:
    explicit DebugWindow(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Окно отладки");
        setMinimumSize(800, 600);
        tabWidget = new QTabWidget(this);
        hashTableView = new QPlainTextEdit(this);
        hashTableView->setReadOnly(true);
        hashTableView->setFont(QFont("Consolas", 10)); 
        tabWidget->addTab(hashTableView, "Хеш-таблица (Питомцы)");
        avlTreeView = new QPlainTextEdit(this);
        avlTreeView->setReadOnly(true);
        avlTreeView->setFont(QFont("Consolas", 10));
        tabWidget->addTab(avlTreeView, "АВЛ-дерево (Визиты)");
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(tabWidget);
        setLayout(layout);
    }
public slots:
    void updateText(const QString &hashTableText, const QString &avlTreeText) {
        hashTableView->setPlainText(hashTableText);
        avlTreeView->setPlainText(avlTreeText);
    }
private:
    QTabWidget *tabWidget;
    QPlainTextEdit *hashTableView;
    QPlainTextEdit *avlTreeView;
};


class ReportDialog : public QDialog {
    Q_OBJECT
public:
    explicit ReportDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Параметры отчета");
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество (оставьте пустым для всех)");
        diagnoseEdit = new QLineEdit(this);
        diagnoseEdit->setPlaceholderText("Оставьте пустым для всех диагнозов");
        startDateEdit = new QLineEdit(this);
        startDateEdit->setPlaceholderText("День Месяц Год (например, 1 январь 2023)");
        endDateEdit = new QLineEdit(this);
        endDateEdit->setPlaceholderText("День Месяц Год (например, 31 декабрь 2023)");
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        formLayout->addRow("Диагноз:", diagnoseEdit);
        formLayout->addRow("Дата начала периода:", startDateEdit);
        formLayout->addRow("Дата окончания периода:", endDateEdit);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
        buttonBox->addButton("Посмотреть отчет", QDialogButtonBox::AcceptRole);
        buttonBox->addButton("Отменить", QDialogButtonBox::RejectRole);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
    }
    ~ReportDialog() {}
    QString ownerFio() const { return ownerFioEdit->text(); }
    QString diagnose() const { return diagnoseEdit->text(); }
    QString startDate() const { return startDateEdit->text(); }
    QString endDate() const { return endDateEdit->text(); }
private:
    QLineEdit *ownerFioEdit;
    QLineEdit *diagnoseEdit;
    QLineEdit *startDateEdit;
    QLineEdit *endDateEdit;
};

class ReportViewWindow : public QWidget {
    Q_OBJECT
public:
    explicit ReportViewWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Результаты отчета");
        setMinimumSize(800, 500);
        reportTableView = new QTableView;
        reportModel = new QStandardItemModel(this);
        reportModel->setHorizontalHeaderLabels({"Кличка", "Владелец", "Вид питомца", "Диагноз", "Врач", "Дата"});
        reportTableView->setModel(reportModel);
        reportTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        reportTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(reportTableView);
        setLayout(layout);
    }
    
    void updateReportData(const vector<ReportEntry>& reportData) { 
        reportModel->removeRows(0, reportModel->rowCount());
        for (const auto& entry : reportData) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(entry.petName))
                   << new QStandardItem(QString::fromStdString(entry.ownerFio))
                   << new QStandardItem(QString::fromStdString(entry.petType))
                   << new QStandardItem(QString::fromStdString(entry.diagnos))
                   << new QStandardItem(QString::fromStdString(entry.doctorFio))
                   << new QStandardItem(QString::fromStdString(entry.date));
            reportModel->appendRow(rowItems);
        }
    }
private:
    QTableView *reportTableView;
    QStandardItemModel *reportModel;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Ветеринарная клиника");
        setMinimumSize(1000, 600);
        createMenusAndToolbar();
        createMainLayout();
        updateTables();
        debugWindow = nullptr;
        reportWindow = nullptr;
    }
    Validator validator;
    ~MainWindow() {}

private slots:
    void loadPets() {
        QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл с данными о питомцах", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
        if (fileName.isEmpty()) return;
        manager.readPetsFile(fileName.toStdString());
        updateTables();
        QMessageBox::information(this, "Успех", "Данные о питомцах успешно загружены.");
    }

    void loadVisits() {
        QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл с данными о визитах", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
        if (fileName.isEmpty()) return;
        manager.readVisitsFile(fileName.toStdString());
        updateTables();
        QMessageBox::information(this, "Успех", "Данные о визитах успешно загружены.");
    }
    
    void savePetsToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл питомцев", "pets_saved.txt", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        // Строка out.setCodec("UTF-8"); УДАЛЕНА

        auto allPets = manager.getAllActivePets();
        for (const auto& pet : allPets) {
            out << QString("%1;%2;%3\n")
                   .arg(QString::fromStdString(pet.key.petName))
                   .arg(QString::fromStdString(pet.key.owner.toStringView()))
                   .arg(QString::fromStdString(pet.type));
        }
        QMessageBox::information(this, "Успех", "Файл питомцев успешно сохранен.");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить файл питомцев.");
    }
}

void saveVisitsToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл визитов", "visits_saved.txt", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        auto allVisits = manager.getAllActiveVisits();
        for (const auto& visit : allVisits) {
            out << QString("%1;%2;%3;%4;%5\n")
                   .arg(QString::fromStdString(visit.key.petName))
                   .arg(QString::fromStdString(visit.key.owner.toStringView()))
                   .arg(QString::fromStdString(visit.diagnos))
                   .arg(QString::fromStdString(visit.doctor.toStringView()))
                   .arg(QString::fromStdString(visit.time.toString()));
        }
        QMessageBox::information(this, "Успех", "Файл визитов успешно сохранен.");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить файл визитов.");
    }
}

    void showAbout() {
        QMessageBox::about(this, "О программе", "<b>Менеджер ветеринарной клиники v1.0</b>");
    }

    void addPet() {
        AddPetDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string petName = dialog.petName().toUtf8().toStdString();
            string ownerFio = dialog.ownerFio().toUtf8().toStdString();
            string petType = dialog.petType().toUtf8().toStdString();
            if (!validator.checkPetName(petName) || !validator.checkFIO(ownerFio) || !validator.checkType(petType)) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат входных данных");
                return;
            }
            string* fioParts = splitstring(ownerFio, ' ');
            if (!fioParts) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат ФИО.");
                return;
            }
            Owner owner(fioParts[0], fioParts[1], fioParts[2]);
            Key key(petName, owner);
            delete[] fioParts;
            if (manager.addPet(key, petType)) {
                updateTables();
            } else {
                QMessageBox::warning(this, "Ошибка", "Питомец с таким ключом уже существует.");
            }
        }
    }

    void addVisit() {
        AddVisitDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string petName = dialog.petName().toUtf8().toStdString();
            string ownerFio = dialog.ownerFio().toUtf8().toStdString();
            string diagnosStr = dialog.diagnosStr().toUtf8().toStdString();
            string doctorStr = dialog.doctorStr().toUtf8().toStdString();
            string timeStr = dialog.timeStr().toUtf8().toStdString();
            if (!validator.checkPetName(petName) || !validator.checkFIO(ownerFio) || 
            diagnosStr.empty() || !validator.checkFIO(doctorStr) || !validator.checkDate(timeStr) ) {
                QMessageBox::warning(this, "Ошибка ввода", "Все поля должны быть заполнены.");
                return;
            }
            string* fioParts = splitstring(ownerFio, ' ');
            if (!fioParts) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат ФИО.");
                return;
            }
            Owner owner(fioParts[0], fioParts[1], fioParts[2]);
            Key key(petName, owner);
            delete[] fioParts;
            string* doctorParts = splitstring(doctorStr, ' ');
            Doctor doctor (doctorParts[0], doctorParts[1], doctorParts[2]);
            delete[] doctorParts;
            string* timeParts = splitstring(timeStr, ' ');
            Time time (stoi(timeParts[0]), timeParts[1], stoi(timeParts[2]));
            delete[] timeParts; 
            if (manager.addVisit(key, diagnosStr, doctor, time)) {
                updateTables();
            } else {
                QMessageBox::warning(this, "Ошибка", "Питомец, для которого добавляется визит, не найден в справочнике питомцев.");
            }
        }
    }

    void removePetBySelection() {
        
        QModelIndexList selection = petsTableView->selectionModel()->selectedRows();
        if (selection.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Выберите питомца для удаления.");
            return;
        }

        //локализация идет нафиг поэтому
        QMessageBox msgBox;
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setText("Удалить выбранного питомца и все связанные с ним визиты?");
        msgBox.setIcon(QMessageBox::Question);
        
        QPushButton* yesB = msgBox.addButton("Да", QMessageBox::YesRole);
        QPushButton* noB = msgBox.addButton("Нет", QMessageBox::NoRole);
        msgBox.setDefaultButton(noB);
        msgBox.exec();
        if ((msgBox.buttonRole(msgBox.clickedButton()) != QMessageBox::YesRole))  return;

        int row = selection.first().row();
        string petName = petsModel->item(row, 0)->text().toUtf8().toStdString();
        string ownerFio = petsModel->item(row, 1)->text().toUtf8().toStdString();
        string petType = petsModel->item(row, 2)->text().toUtf8().toStdString();
        string* fioParts = splitstring(ownerFio, ' ');
        if (!fioParts) {
            QMessageBox::critical(this, "Критическая ошибка", "Не удалось разобрать ФИО из таблицы.");
            return;
        }
        Owner owner(fioParts[0], fioParts[1], fioParts[2]);
        Key key(petName, owner);
        delete[] fioParts;
        if (manager.removePet(key, petType)) {
            updateTables(); 
            QMessageBox::information(this, "Успех", "Питомец успешно удален.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить питомца. Возможно, данные в таблице устарели.");
        }
    }

    void removePetByDialog() {
        RemovePetDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string petName = dialog.petName().toUtf8().toStdString();
            string ownerFio = dialog.ownerFio().toUtf8().toStdString();
            string petType = dialog.petType().toUtf8().toStdString();
            if (!validator.checkPetName(petName) || !validator.checkFIO(ownerFio) || !validator.checkType(petType)) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат входных данных.");
                return;
            }
            string* fioParts = splitstring(ownerFio, ' ');
            if (!fioParts) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат ФИО.");
                return;
            }
            Owner owner(fioParts[0], fioParts[1], fioParts[2]);
            Key key(petName, owner);
            delete[] fioParts;
            if (manager.removePet(key, petType)) {
                updateTables();
                QMessageBox::information(this, "Успех", "Питомец успешно удален.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить питомца. Проверьте введенные данные.");
            }
        }
    }

    void removeVisitBySelection() {
        QModelIndexList selection = visitsTableView->selectionModel()->selectedRows();
        if (selection.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите визит для удаления.");
            return;
        }
        auto reply = QMessageBox::question(this, "Подтверждение", "Вы уверены, что хотите удалить выбранную запись о визите?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
        int row = selection.first().row();
        string petNameStr = visitsModel->item(row, 0)->text().toUtf8().toStdString();
        string ownerFioStr = visitsModel->item(row, 1)->text().toUtf8().toStdString();
        string diagnosStr = visitsModel->item(row, 2)->text().toUtf8().toStdString();
        string doctorFioStr = visitsModel->item(row, 3)->text().toUtf8().toStdString();
        string dateStr = visitsModel->item(row, 4)->text().toUtf8().toStdString();
        string* ownerParts = splitstring(ownerFioStr, ' ');    
        if (!ownerParts) {
            QMessageBox::critical(this, "Критическая ошибка", "Не удалось разобрать ФИО владельца из таблицы.");
            return;
        }
        Owner owner(ownerParts[0], ownerParts[1], ownerParts[2]);
        Key key(petNameStr, owner);
        delete[] ownerParts;
        string* doctorParts = splitstring(doctorFioStr, ' ');
        if (!doctorParts) {
            QMessageBox::critical(this, "Критическая ошибка", "Не удалось разобрать ФИО доктора из таблицы.");
            return;
        }
        Doctor doctor(doctorParts[0], doctorParts[1], doctorParts[2]);
        delete[] doctorParts;
        string* dateParts = splitstring(dateStr,  ' ');
        if (!dateParts) {
            QMessageBox::critical(this, "Критическая ошибка", "Не удалось разобрать дату из таблицы.");
            return;
        }
        Time time = Time(stoi(dateParts[0]), dateParts[1], stoi(dateParts[2]));
        delete[] dateParts; 
        if (manager.removeVisit(key, diagnosStr, doctor, time)) {
            updateTables();
            QMessageBox::information(this, "Успех", "Запись о визите успешно удалена.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись о визите. Запись не найдена в структурах данных.");
        }
    }

    void removeVisitByDialog() {
        RemoveVisitDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string petName = dialog.petName().toUtf8().toStdString();
            string ownerFio = dialog.ownerFio().toUtf8().toStdString();
            string diagnosStr = dialog.diagnosStr().toUtf8().toStdString();
            string doctorStr = dialog.doctorStr().toUtf8().toStdString();
            string timeStr = dialog.timeStr().toUtf8().toStdString();
            if (!validator.checkPetName(petName) || !validator.checkFIO(ownerFio) || 
            diagnosStr.empty() || !validator.checkFIO(doctorStr) || !validator.checkDate(timeStr) ) {
                QMessageBox::warning(this, "Ошибка ввода", "Все поля должны быть заполнены.");
                return;
            }
            string* fioParts = splitstring(ownerFio, ' ');
            if (!fioParts) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат ФИО.");
                return;
            }
            Owner owner(fioParts[0], fioParts[1], fioParts[2]);
            Key key(petName, owner);
            delete[] fioParts;
            string* doctorParts = splitstring(doctorStr, ' ');
            Doctor doctor(doctorParts[0], doctorParts[1], doctorParts[2]);
            delete[] doctorParts;
            string* timeParts = splitstring(timeStr, ' ');
            Time time(stoi(timeParts[0]), timeParts[1], stoi(timeParts[2]));
            delete[] timeParts; 
            if (manager.removeVisit(key, diagnosStr, doctor, time)) {
                updateTables();
                QMessageBox::information(this, "Успех", "Запись о визите успешно удалена.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись о визите. Проверьте введенные данные.");
            }
        }
    }

    void showReportDialog() {
        ReportDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string ownerFio = dialog.ownerFio().toStdString();
            string diagnose = dialog.diagnose().toStdString();
            string startDateStr = dialog.startDate().toStdString();
            string endDateStr = dialog.endDate().toStdString();
            if (startDateStr.empty() || endDateStr.empty() || !validator.checkDate(startDateStr) || !validator.checkDate(endDateStr)) {
                QMessageBox::warning(this, "Ошибка ввода", "Даты начала и окончания периода должны быть заполнены и корректны.");
                return;
            }
            string* startParts = splitstring(startDateStr, ' ');
            string* endParts = splitstring(endDateStr, ' ');
            if (!startParts || !endParts) {
                QMessageBox::critical(this, "Ошибка", "Не удалось разобрать даты.");
                if(startParts) delete[] startParts;
                if(endParts) delete[] endParts;
                return;
            }
            Time startDate(stoi(startParts[0]), startParts[1], stoi(startParts[2]));
            Time endDate(stoi(endParts[0]), endParts[1], stoi(endParts[2]));
            delete[] startParts;
            delete[] endParts;
            auto reportResults = manager.generateReport(ownerFio, diagnose, startDate, endDate);
            if (reportWindow == nullptr) {
                reportWindow = new ReportViewWindow(); 
            }
            reportWindow->updateReportData(reportResults);
            reportWindow->show();
            reportWindow->raise(); 
            reportWindow->activateWindow(); 
        }
    }

    void showDebugWindow() {
        if (debugWindow == nullptr) {
            debugWindow = new DebugWindow(this);
        }
        string treeStr = manager.getStringDebugTree();
        string tableStr = manager.getStringDebugTable();
        debugWindow->updateText(
            QString::fromStdString(tableStr),
            QString::fromStdString(treeStr)
        );
        debugWindow->show();
        debugWindow->raise();
        debugWindow->activateWindow();
    }

private:
    void createMenusAndToolbar() {
        QMenu *fileMenu = menuBar()->addMenu("&Файл");
        QMenu *loadMenu = fileMenu->addMenu("&Загрузить");
        QAction *loadPetsAction = new QAction("Питомцев из файла...", this);
        connect(loadPetsAction, &QAction::triggered, this, &MainWindow::loadPets);
        loadMenu->addAction(loadPetsAction);
        QAction *loadVisitsAction = new QAction("Визиты из файла...", this);
        connect(loadVisitsAction, &QAction::triggered, this, &MainWindow::loadVisits);
        loadMenu->addAction(loadVisitsAction);
        QMenu *saveMenu = fileMenu->addMenu("&Сохранить");
        QAction *savePetsAction = new QAction("Питомцев в файл...", this);
        connect(savePetsAction, &QAction::triggered, this, &MainWindow::savePetsToFile);
        saveMenu->addAction(savePetsAction);
        QAction *saveVisitsAction = new QAction("Визиты в файл...", this);
        connect(saveVisitsAction, &QAction::triggered, this, &MainWindow::saveVisitsToFile);
        saveMenu->addAction(saveVisitsAction);
        fileMenu->addSeparator();
        QAction *exitAction = new QAction("&Выход", this);
        connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
        fileMenu->addAction(exitAction);

        QMenu *editMenu = menuBar()->addMenu("&Правка");
        QMenu *addMenu = editMenu->addMenu("&Добавить");
        QAction *addPetAction = new QAction("Добавить питомца...", this);
        connect(addPetAction, &QAction::triggered, this, &MainWindow::addPet);
        addMenu->addAction(addPetAction);
        QAction *addVisitAction = new QAction("Добавить визит...", this);
        connect(addVisitAction, &QAction::triggered, this, &MainWindow::addVisit);
        addMenu->addAction(addVisitAction);
        editMenu->addSeparator();
        QMenu *removeMenu = editMenu->addMenu("&Удалить");
        QMenu *removePetSubMenu = removeMenu->addMenu("Удалить питомца");
        QAction* removePetSelectionAction = new QAction("Удалить выделенного", this);
        connect(removePetSelectionAction, &QAction::triggered, this, &MainWindow::removePetBySelection);
        removePetSubMenu->addAction(removePetSelectionAction);
        QAction* removePetDialogAction = new QAction("Удалить по данным...", this);
        connect(removePetDialogAction, &QAction::triggered, this, &MainWindow::removePetByDialog);
        removePetSubMenu->addAction(removePetDialogAction);
        QMenu *removeVisitSubMenu = removeMenu->addMenu("Удалить визит");
        QAction* removeVisitSelectionAction = new QAction("Удалить выделенный", this);
        connect(removeVisitSelectionAction, &QAction::triggered, this, &MainWindow::removeVisitBySelection);
        removeVisitSubMenu->addAction(removeVisitSelectionAction);
        QAction* removeVisitDialogAction = new QAction("Удалить по данным...", this);
        connect(removeVisitDialogAction, &QAction::triggered, this, &MainWindow::removeVisitByDialog);
        removeVisitSubMenu->addAction(removeVisitDialogAction);

        QMenu *reportMenu = menuBar()->addMenu("&Отчет");
        QAction *generateReportAction = new QAction("Сформировать отчет...", this);
        connect(generateReportAction, &QAction::triggered, this, &MainWindow::showReportDialog);
        reportMenu->addAction(generateReportAction);

        QMenu *helpMenu = menuBar()->addMenu("&Справка");
        QAction *aboutAction = new QAction("&О программе", this);
        connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
        helpMenu->addAction(aboutAction);
        QMenu* debugMenu = helpMenu->addMenu("Отладка");
        QAction *showBothDebugAction = new QAction("Показать всё", this);
        showBothDebugAction->setShortcut(QKeySequence(Qt::Key_F12));
        connect(showBothDebugAction, &QAction::triggered, this, &MainWindow::showDebugWindow);
        debugMenu->addAction(showBothDebugAction);
    }

    void createMainLayout() {
        petsTableView = new QTableView;
        petsModel = new QStandardItemModel(this);
        petsModel->setHorizontalHeaderLabels({"Кличка", "Владелец", "Вид"});
        petsTableView->setModel(petsModel);
        petsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        petsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        petsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QVBoxLayout *petsLayout = new QVBoxLayout;
        petsLayout->addWidget(new QLabel("<h3>Питомцы (Хэш-таблица)</h3>"));
        petsLayout->addWidget(petsTableView);

        visitsTableView = new QTableView;
        visitsModel = new QStandardItemModel(this);
        visitsModel->setHorizontalHeaderLabels({"Кличка", "Владелец", "Диагноз", "Врач", "Дата"});
        visitsTableView->setModel(visitsModel);
        visitsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        visitsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        visitsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QVBoxLayout *visitsLayout = new QVBoxLayout;
        visitsLayout->addWidget(new QLabel("<h3>Консультации (АВЛ-дерево)</h3>"));
        visitsLayout->addWidget(visitsTableView);

        QHBoxLayout *mainLayout = new QHBoxLayout;
        mainLayout->addLayout(petsLayout);
        mainLayout->addLayout(visitsLayout);
        QWidget *centralWidget = new QWidget;
        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);
    }
    
    void updateTables() {
        updatePetsTable();
        updateVisitsTable();
    }

    void updatePetsTable() {
        petsModel->removeRows(0, petsModel->rowCount());
        auto activePets = manager.getAllActivePets();
        for (const auto& pet : activePets) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(pet.key.petName))
                   << new QStandardItem(QString::fromStdString(pet.key.owner.toStringView())) 
                   << new QStandardItem(QString::fromStdString(pet.type));
            petsModel->appendRow(rowItems);
        }
    }

    void updateVisitsTable() {
        visitsModel->removeRows(0, visitsModel->rowCount());
        auto activeVisits = manager.getAllActiveVisits();
        for (const auto& visit : activeVisits) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(visit.key.petName))
                   << new QStandardItem(QString::fromStdString(visit.key.owner.toStringView()))
                   << new QStandardItem(QString::fromStdString(visit.diagnos))
                   << new QStandardItem(QString::fromStdString(visit.doctor.toStringView()))
                   << new QStandardItem(QString::fromStdString(visit.time.toString()));
            visitsModel->appendRow(rowItems);
        }
    }

    Manager manager;
    QTableView* petsTableView;
    QTableView* visitsTableView;
    QStandardItemModel* petsModel;
    QStandardItemModel* visitsModel;
    DebugWindow *debugWindow;
    ReportViewWindow *reportWindow;
};

#endif // MAIN_WINDOW_HPP