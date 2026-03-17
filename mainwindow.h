#pragma once

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTimer>
#include <QVector>
#include <functional>

// ─── Dati ──────────────────────────────────────────────────────────────────

struct SymbolItem {
    QString sym;    // il carattere
    QString label;  // nome breve
};

struct Category {
    QString         name;
    QVector<SymbolItem> items;
};

// ─── Chip cliccabile ───────────────────────────────────────────────────────

class SymbolChip : public QFrame
{
public:
    explicit SymbolChip(const QString &sym,
                        const QString &label,
                        QWidget       *parent = nullptr);

    void flash();  // feedback visivo "copiato"

    std::function<void(const QString &sym, const QString &label)> onClicked;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event)      override;
    void leaveEvent(QEvent *event)           override;

private:
    void applyStyle(bool hovered, bool copied);

    QString m_sym;
    QString m_label;
    QLabel *m_symLabel  = nullptr;
    QLabel *m_nameLabel = nullptr;
};

// ─── Finestra principale ───────────────────────────────────────────────────

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void buildData();
    void buildUi();
    void rebuildContent(const QString &filter = {});
    void showToast(const QString &msg);

    QLineEdit   *m_search          = nullptr;
    QWidget     *m_container       = nullptr;
    QVBoxLayout *m_containerLayout = nullptr;
    QLabel      *m_toast           = nullptr;
    QTimer      *m_toastTimer      = nullptr;

    QVector<Category> m_data;

protected:
    void resizeEvent(QResizeEvent *event) override;
};
