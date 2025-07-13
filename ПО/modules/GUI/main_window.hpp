#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
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
#include <QTabWidget>   
#include <QPushButton>
#include <QSpinBox>
#include "../Manager/Manager.hpp"
#include "../HelpFunction.hpp"
#include "../Validator.hpp"



class InitSizeDialog : public QDialog {
    Q_OBJECT
public:
    explicit InitSizeDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Начальная настройка");
        setModal(true); 

        sizeSpinBox = new QSpinBox(this);
        sizeSpinBox->setMinimum(10);     
        sizeSpinBox->setMaximum(10000);   
        sizeSpinBox->setValue(100);       

        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Начальный размер хеш-таблицы:", sizeSpinBox);
        
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
        setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    }

    int getInitialSize() const {
        return sizeSpinBox->value();
    }

private:
    QSpinBox *sizeSpinBox;
};



class AddPetDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddPetDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Добавить нового питомца");
        petNameEdit = new QLineEdit(this);
        petNameEdit->setPlaceholderText("С большой буквы");
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        petTypeEdit = new QLineEdit(this);
        petTypeEdit->setPlaceholderText("Например: кот, собака, попугай");
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        formLayout->addRow("Вид питомца:", petTypeEdit);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        buttonBox->button(QDialogButtonBox::Ok)->setText("Добавить");
        buttonBox->button(QDialogButtonBox::Cancel)->setText("Назад");

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

class FindVisitsDialog : public QDialog {
    Q_OBJECT
public:
    explicit FindVisitsDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Найти визиты по питомцу");
        petNameEdit = new QLineEdit(this);
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка питомца:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        buttonBox->button(QDialogButtonBox::Ok)->setText("Поиск");
        buttonBox->button(QDialogButtonBox::Cancel)->setText("Назад");
        
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
    }
    ~FindVisitsDialog() {}
    QString petName() const { return petNameEdit->text(); }
    QString ownerFio() const { return ownerFioEdit->text(); }
private:
    QLineEdit *petNameEdit;
    QLineEdit *ownerFioEdit;
};

class AddVisitDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddVisitDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Добавить новый  прием");
        petNameEdit = new QLineEdit(this);
        petNameEdit->setPlaceholderText("С большой буквы");
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        diagnoseEdit = new QLineEdit(this);
        doctorFioEdit = new QLineEdit(this);
        doctorFioEdit->setPlaceholderText("Фамилия Имя Отчество");
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

        buttonBox->button(QDialogButtonBox::Ok)->setText("Добавить");
        buttonBox->button(QDialogButtonBox::Cancel)->setText("Назад");

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
        petNameEdit->setPlaceholderText("С большой буквы");
        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");
        petTypeEdit = new QLineEdit(this);
        petTypeEdit->setPlaceholderText("Например: кот, собака, попугай");
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);
        formLayout->addRow("Вид питомца:", petTypeEdit);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        buttonBox->button(QDialogButtonBox::Ok)->setText("Удалить");
        buttonBox->button(QDialogButtonBox::Cancel)->setText("Назад");

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
        setWindowTitle("Удалить  прием");
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

        buttonBox->button(QDialogButtonBox::Ok)->setText("Удалить");
        buttonBox->button(QDialogButtonBox::Cancel)->setText("Назад");

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
        tabWidget->addTab(avlTreeView, "АВЛ-дерево (Приемы)");
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
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество (оставить пустым для всех)");
        diagnoseEdit = new QLineEdit(this);
        diagnoseEdit->setPlaceholderText("Оставить пустым для всех диагнозов");
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
        buttonBox->addButton("Сформировать", QDialogButtonBox::AcceptRole);
        buttonBox->addButton("Назад", QDialogButtonBox::RejectRole);
        
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
        
        QPushButton *saveButton = new QPushButton("Сохранить отчет в файл...", this);
        connect(saveButton, &QPushButton::clicked, this, &ReportViewWindow::saveReportToFile);
        
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(reportTableView);
        layout->addWidget(saveButton);
        setLayout(layout);
    }
    
    void updateReportData(const ReportEntry* reportData, int count) { 
        reportModel->removeRows(0, reportModel->rowCount());
        for (int i = 0; i < count; ++i) {
            const auto& entry = reportData[i];
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



private slots:
    void saveReportToFile() {
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить отчет", "report.txt", "Текстовые файлы (*.txt);;Все файлы (*.*)");
        if (fileName.isEmpty()) {
            return;
        }

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int row = 0; row < reportModel->rowCount(); ++row) {
                QStringList rowData;
                for (int col = 0; col < reportModel->columnCount(); ++col) {
                    rowData << reportModel->item(row, col)->text();
                }
                out << rowData.join(";") << "\n";
            }
            QMessageBox::information(this, "Успех", "Отчет успешно сохранен.");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось сохранить файл отчета.");
        }
    }

private:
    QTableView *reportTableView;
    QStandardItemModel *reportModel;
};


class FindPetDialog : public QDialog {
    Q_OBJECT
public:
    explicit FindPetDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Найти питомца");

        petNameEdit = new QLineEdit(this);
        petNameEdit->setPlaceholderText("С большой буквы");

        ownerFioEdit = new QLineEdit(this);
        ownerFioEdit->setPlaceholderText("Фамилия Имя Отчество");

        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Кличка питомца:", petNameEdit);
        formLayout->addRow("ФИО Владельца:", ownerFioEdit);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        buttonBox->button(QDialogButtonBox::Ok)->setText("Поиск");
        buttonBox->button(QDialogButtonBox::Cancel)->setText("Назад");

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonBox);
    }

    ~FindPetDialog() {}

    QString petName() const { return petNameEdit->text(); }
    QString ownerFio() const { return ownerFioEdit->text(); }

private:
    QLineEdit *petNameEdit;
    QLineEdit *ownerFioEdit;
};






class MainWindow : public QMainWindow {
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
        if (manager.getVisitsCount() == 0 ){
            QMessageBox::information(this, "Успешно, но", "Нет записей для существующих питомцев");
        }else QMessageBox::information(this, "Успех", "Данные о визитах успешно загружены.");
    }
    
    void savePetsToFile() {
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл питомцев", "changePets.txt", "Текстовые файлы (*.txt)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            recordPet* petsArray = manager.getPetsArray();
            int petsCount = manager.getPetsCount();
            for (int i = 0; i < petsCount; ++i) {
                const auto& pet = petsArray[i];
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
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл визитов", "changeVisits.txt", "Текстовые файлы (*.txt)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            recordVisit* visitsArray = manager.getVisitsArray();
            int visitsCount = manager.getVisitsCount();
            for (int i = 0; i < visitsCount; ++i) {
                const auto& visit = visitsArray[i];
                out << QString("%1;%2;%3;%4;%5\n")
                    .arg(QString::fromStdString(visit.key.petName))
                    .arg(QString::fromStdString(visit.key.owner.toStringView()))
                    .arg(QString::fromStdString(visit.diagnos))
                    .arg(QString::fromStdString(visit.doctor.toStringView()))
                    .arg(QString::fromStdString(visit.date.toString()));
            }
            QMessageBox::information(this, "Успех", "Файл визитов успешно сохранен.");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось сохранить файл визитов.");
        }
    }

    void showAbout() {
        QMessageBox::about(this, "О программе", "<b> ПО для предметной области Ветеринарная клиники. Ткачев Б9123-09.03.04</b>");
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
                QMessageBox::warning(this, "Ошибка", "Питомец с таким ключом уже существует или достигнут лимит записей.");
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
            Date date (stoi(timeParts[0]), timeParts[1], stoi(timeParts[2]));
            delete[] timeParts; 
            if (manager.addVisit(key, diagnosStr, doctor, date)) {
                updateTables();
            } else {
                QMessageBox::warning(this, "Ошибка", "Питомец не найден или достигнут лимит записей о визитах.");
            }
        }
    }

    void removePetBySelection() {
        QModelIndexList selection = petsTableView->selectionModel()->selectedRows();
        if (selection.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Выберите питомца для удаления.");
            return;
        }

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
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите  прием для удаления.");
            return;
        }
        auto reply = QMessageBox::question(this, "Подтверждение", "Вы уверены, что хотите удалить выбранную запись о  приеме?", QMessageBox::Yes | QMessageBox::No);
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
        Date date = Date(stoi(dateParts[0]), dateParts[1], stoi(dateParts[2]));
        delete[] dateParts; 
        if (manager.removeVisit(key, diagnosStr, doctor, date)) {
            updateTables();
            QMessageBox::information(this, "Успех", "Запись о  приеме успешно удалена.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись о  приеме. Запись не найдена в структурах данных.");
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
            Date date(stoi(timeParts[0]), timeParts[1], stoi(timeParts[2]));
            delete[] timeParts; 
            if (manager.removeVisit(key, diagnosStr, doctor, date)) {
                updateTables();
                QMessageBox::information(this, "Успех", "Запись о  приеме успешно удалена.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись о  приеме. Проверьте введенные данные.");
            }
        }
    }


    void findVisits() {
        FindVisitsDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string petName = dialog.petName().toUtf8().toStdString();
            string ownerFio = dialog.ownerFio().toUtf8().toStdString();

            if (!validator.checkPetName(petName) || !validator.checkFIO(ownerFio)) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат входных данных.");
                updateVisitsTable();
                return;
            }

            string* fioParts = splitstring(ownerFio, ' ');
            if (!fioParts) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат ФИО.");
                updateVisitsTable();
                return;
            }
            Owner owner(fioParts[0], fioParts[1], fioParts[2]);
            Key key(petName, owner);
            delete[] fioParts;

            recordVisit foundVisitsArray[1000]; 
            int foundCount = 0;
            int searchSteps = 0; 

            manager.findVisits(key, foundVisitsArray, foundCount, searchSteps);

            updateVisitsTable(foundVisitsArray, foundCount);

            QString message = QString("Поиск завершен. Найдено: %1 визитов. Шагов для поиска в дереве: %2.")
                                  .arg(foundCount)
                                  .arg(searchSteps);
            QMessageBox::information(this, "Результаты поиска", message);
        } else {
            updateVisitsTable();
        }
    }


    void findAndShowPet() {
        FindPetDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string petName = dialog.petName().toUtf8().toStdString();
            string ownerFio = dialog.ownerFio().toUtf8().toStdString();

            if (!validator.checkPetName(petName) || !validator.checkFIO(ownerFio)) {
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

            optional<recordPet> foundPet = manager.findPet(key);

            if (foundPet) {
                QString petInfo = QString("<b>Кличка:</b> %1<br>"
                                          "<b>Владелец:</b> %2<br>"
                                          "<b>Вид:</b> %3")
                                      .arg(QString::fromStdString(foundPet->key.petName))
                                      .arg(QString::fromStdString(foundPet->key.owner.toStringView()))
                                      .arg(QString::fromStdString(foundPet->type));
                
                QMessageBox::information(this, "Питомец найден", petInfo);
            } else {
                QMessageBox::information(this, "Результат поиска", "Питомец с такими данными не найден.");
            }
        }
    }


    Date helpFunc(string str){
        string* strParts = splitstring(str, ' ');
        Date date(stoi(strParts[0]), strParts[1], stoi(strParts[2]));
        delete[] strParts;

        return date;
    
    }

    void showReportDialog() {
        ReportDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            string ownerFio = dialog.ownerFio().toStdString();
            string diagnose = dialog.diagnose().toStdString();
            string startDateStr = dialog.startDate().toStdString();
            string endDateStr = dialog.endDate().toStdString();

            if (ownerFio.empty() && diagnose.empty() && startDateStr.empty() && endDateStr.empty()) {
                QMessageBox::warning(this, "Ошибка ввода", "Необходимо указать хотя бы один фильтр.");
                return;
            }

            if (!ownerFio.empty() && !validator.checkFIO(ownerFio)) {
                QMessageBox::warning(this, "Ошибка ввода", "Неверный формат ФИО владельца.");
                return;
            }
            
            Date startDate, endDate;
            
            if (!startDateStr.empty() && !endDateStr.empty()) {
                if (!validator.checkDate(startDateStr) || !validator.checkDate(endDateStr)) {
                    QMessageBox::warning(this, "Ошибка ввода", "Неверный формат одной из дат.");
                    return;
                }
                startDate = helpFunc(startDateStr);
                endDate = helpFunc(endDateStr);
                if (endDate < startDate) {
                    QMessageBox::warning(this, "Ошибка ввода", "Дата окончания периода должна быть не раньше даты начала.");
                    return;
                }
            } 
            else if (!startDateStr.empty()) {
                if (!validator.checkDate(startDateStr)) {
                    QMessageBox::warning(this, "Ошибка ввода", "Неверный формат даты начала периода.");
                    return;
                }
                startDate = helpFunc(startDateStr);
                endDate = Date(31, "декабрь", 2025);
            }
            else if (!endDateStr.empty()) {
                if (!validator.checkDate(endDateStr)) {
                    QMessageBox::warning(this, "Ошибка ввода", "Неверный формат даты окончания периода.");
                    return;
                }
                startDate = Date(1, "январь", 2000);
                endDate = helpFunc(endDateStr);
            }
            else {
                startDate = Date(1, "январь", 2000);
                endDate = Date(31, "декабрь", 2025);
            }

            ReportEntry reportData[1000];

            int entryCount = manager.generateReport(
                ownerFio, 
                diagnose,
                startDate, 
                endDate,
                reportData
            );

            if (entryCount == 0) {
                QMessageBox::information(this, "Результат", "По заданным критериям ничего не найдено.");
                return;
            }

            if (reportWindow == nullptr) {
                reportWindow = new ReportViewWindow(); 
            }
            
            reportWindow->updateReportData(reportData, entryCount);
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


    void showSetInitialSizeDialog() {
        InitSizeDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            int newSize = dialog.getInitialSize();
            if (manager.reinitializeHashTable(newSize)) {
                QMessageBox::information(this, "Успех", QString("Размер хеш-таблицы успешно установлен на %1.").arg(newSize));
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось изменить размер хеш-таблицы. В ней уже есть данные.");
            }
        }
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

        QMenu *settingsMenu = menuBar()->addMenu("&Настройка");
        QAction *setSizeAction = new QAction("Задать размер таблицы...", this);
        connect(setSizeAction, &QAction::triggered, this, &MainWindow::showSetInitialSizeDialog);
        settingsMenu->addAction(setSizeAction);

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
        
        QMenu *findMenu = editMenu->addMenu("&Найти");
        QAction *findPetAction = new QAction("Найти питомца...", this);
        connect(findPetAction, &QAction::triggered, this, &MainWindow::findAndShowPet);
        findMenu->addAction(findPetAction);
        QAction *findVisitsAction = new QAction("Найти визиты...", this);
        connect(findVisitsAction, &QAction::triggered, this, &MainWindow::findVisits);
        findMenu->addAction(findVisitsAction);

        editMenu->addSeparator();

        QMenu *addMenu = editMenu->addMenu("&Добавить");
        QAction *addPetAction = new QAction("Добавить питомца...", this);
        connect(addPetAction, &QAction::triggered, this, &MainWindow::addPet);
        addMenu->addAction(addPetAction);
        QAction *addVisitAction = new QAction("Добавить  прием...", this);
        connect(addVisitAction, &QAction::triggered, this, &MainWindow::addVisit);
        addMenu->addAction(addVisitAction);
        
        QMenu *removeMenu = editMenu->addMenu("&Удалить");
        QMenu *removePetSubMenu = removeMenu->addMenu("Удалить питомца");
        QAction* removePetSelectionAction = new QAction("Удалить выделенного", this);
        connect(removePetSelectionAction, &QAction::triggered, this, &MainWindow::removePetBySelection);
        removePetSubMenu->addAction(removePetSelectionAction);
        QAction* removePetDialogAction = new QAction("Удалить по данным...", this);
        connect(removePetDialogAction, &QAction::triggered, this, &MainWindow::removePetByDialog);
        removePetSubMenu->addAction(removePetDialogAction);
        
        QMenu *removeVisitSubMenu = removeMenu->addMenu("Удалить  прием");
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
        helpMenu->addSeparator();
        QAction *debugAction = new QAction("Отладка", this);
        debugAction->setShortcut(QKeySequence(Qt::Key_F12));
        connect(debugAction, &QAction::triggered, this, &MainWindow::showDebugWindow);
        helpMenu->addAction(debugAction);
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
        petsLayout->addWidget(new QLabel("<h3>Питомцы</h3>"));
        petsLayout->addWidget(petsTableView);

        visitsTableView = new QTableView;
        visitsModel = new QStandardItemModel(this);
        visitsModel->setHorizontalHeaderLabels({"Кличка", "Владелец", "Диагноз", "Врач", "Дата"});
        visitsTableView->setModel(visitsModel);
        visitsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        visitsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        visitsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        
        QPushButton* resetVisitsFilterButton = new QPushButton("Показать все визиты");
        connect(resetVisitsFilterButton, &QPushButton::clicked, this, &MainWindow::updateTables);

        QVBoxLayout *visitsLayout = new QVBoxLayout;
        visitsLayout->addWidget(new QLabel("<h3>Приемы</h3>"));
        visitsLayout->addWidget(visitsTableView);
        visitsLayout->addWidget(resetVisitsFilterButton); 

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
        recordPet* petsArray = manager.getPetsArray();
        int petsCount = manager.getPetsCount();
        for (int i = 0; i < petsCount; ++i) {
            const auto& pet = petsArray[i];
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(pet.key.petName))
                   << new QStandardItem(QString::fromStdString(pet.key.owner.toStringView()))
                   << new QStandardItem(QString::fromStdString(pet.type));
            petsModel->appendRow(rowItems);
        }
    }


    void updateVisitsTable(recordVisit* filteredArray = nullptr, int filteredCount = -1) {
        recordVisit* visitsArray;
        int visitsCount;

        if (filteredArray != nullptr && filteredCount != -1) {
            visitsArray = filteredArray;
            visitsCount = filteredCount;
        } else {
            visitsArray = manager.getVisitsArray();
            visitsCount = manager.getVisitsCount();
        }
        
        visitsModel->removeRows(0, visitsModel->rowCount());
        for (int i = 0; i < visitsCount; ++i) {
            const auto& visit = visitsArray[i];
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(visit.key.petName))
                << new QStandardItem(QString::fromStdString(visit.key.owner.toStringView()))
                << new QStandardItem(QString::fromStdString(visit.diagnos))
                << new QStandardItem(QString::fromStdString(visit.doctor.toStringView()))
                << new QStandardItem(QString::fromStdString(visit.date.toString()));
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

#endif