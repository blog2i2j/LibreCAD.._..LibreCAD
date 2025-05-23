#ifndef COLORWIZARD_H
#define COLORWIZARD_H

#include <memory>
#include <QFrame>

class QListWidgetItem;

namespace Ui
{
    class ColorWizard;
}

class ColorWizard : public QFrame{
    Q_OBJECT
public:
    explicit ColorWizard(QWidget* parent = nullptr);
    ~ColorWizard();
    QStringList getFavList();
    void addFavorite(QString color);
private:
    std::unique_ptr<Ui::ColorWizard> ui;
signals:
    void requestingColorChange(QColor);
    void requestingSelection(QColor);
    void colorDoubleClicked(QColor);
protected slots:
    void requestColorChange();
    void requestSelection();
    void invokeColorDialog();
    void addOrRemove();
    void removeFavorite();
    void handleDoubleClick(QListWidgetItem* item);
};

#endif // COLORWIZARD_H
