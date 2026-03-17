#include "mainwindow.h"
#include "flowlayout.h"

#include <QApplication>
#include <QClipboard>
#include <QScrollArea>
#include <QScrollBar>
#include <QMouseEvent>
#include <QTimer>
#include <QResizeEvent>
#include <QFont>
#include <QColor>

namespace {

QString cssColor(const QColor &color)
{
    return color.name(QColor::HexRgb);
}

} // namespace

// ═══════════════════════════════════════════════════════════════════════════
//  SymbolChip
// ═══════════════════════════════════════════════════════════════════════════

SymbolChip::SymbolChip(const QString &sym, const QString &label, QWidget *parent)
    : QFrame(parent), m_sym(sym), m_label(label)
{
    setFixedSize(84, 56);
    setCursor(Qt::PointingHandCursor);
    setToolTip(QString("Copia  %1  (%2)").arg(sym, label));
    setFrameShape(QFrame::NoFrame);

    auto *vl = new QVBoxLayout(this);
    vl->setContentsMargins(4, 4, 4, 3);
    vl->setSpacing(1);

    m_symLabel = new QLabel(sym, this);
    m_symLabel->setAlignment(Qt::AlignCenter);
    m_symLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont sf = m_symLabel->font();
    sf.setPixelSize(20);
    m_symLabel->setFont(sf);

    m_nameLabel = new QLabel(label, this);
    m_nameLabel->setAlignment(Qt::AlignCenter);
    m_nameLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    // testo truncato se troppo lungo
    m_nameLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    QFont nf = m_nameLabel->font();
    nf.setPixelSize(10);
    m_nameLabel->setFont(nf);

    vl->addWidget(m_symLabel);
    vl->addWidget(m_nameLabel);

    applyStyle(false, false);
}

void SymbolChip::applyStyle(bool hovered, bool copied)
{
    QString bg, border, symColor, nameColor;
    const bool darkTheme = palette().color(QPalette::Window).lightnessF() < 0.5;

    if (copied) {
        if (darkTheme) {
            bg        = "#163127";
            border    = "#3ecf8e";
            symColor  = "#f3fff8";
            nameColor = "#c9f6dc";
        } else {
            bg        = "#dcfce7";
            border    = "#22c55e";
            symColor  = "#14532d";
            nameColor = "#166534";
        }
    } else if (hovered) {
        if (darkTheme) {
            bg        = "#1d2738";
            border    = "#7aa2ff";
            symColor  = "#f8fbff";
            nameColor = "#dbe7ff";
        } else {
            bg        = "#eef4ff";
            border    = "#6f8fe8";
            symColor  = "#0f172a";
            nameColor = "#334155";
        }
    } else {
        if (darkTheme) {
            bg        = "#20242c";
            border    = "#475061";
            symColor  = "#f5f7fa";
            nameColor = "#d1d8e2";
        } else {
            bg        = "#f7f8fa";
            border    = "#c4cbd5";
            symColor  = "#111827";
            nameColor = "#475569";
        }
    }

    setStyleSheet(QString(
        "SymbolChip {"
        "  background:%1;"
        "  border:1px solid %2;"
        "  border-radius:6px;"
        "}"
    ).arg(bg, border));

    m_symLabel->setStyleSheet(
        QString("color:%1;background:transparent;").arg(symColor));
    m_nameLabel->setStyleSheet(
        QString("color:%1;background:transparent;").arg(nameColor));
}

void SymbolChip::mousePressEvent(QMouseEvent *event)
{
    QFrame::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        flash();
        if (onClicked) onClicked(m_sym, m_label);
    }
}

void SymbolChip::enterEvent(QEnterEvent *event)
{
    QFrame::enterEvent(event);
    applyStyle(true, false);
}

void SymbolChip::leaveEvent(QEvent *event)
{
    QFrame::leaveEvent(event);
    applyStyle(false, false);
}

void SymbolChip::flash()
{
    applyStyle(false, true);
    QTimer::singleShot(700, this, [this]() { applyStyle(false, false); });
}

// ═══════════════════════════════════════════════════════════════════════════
//  Dati simboli
// ═══════════════════════════════════════════════════════════════════════════

void MainWindow::buildData()
{
    m_data = {
        { "Elenchi puntati", {
            {"•",  "bullet"},    {"·",   "punto med."},  {"‣",  "triangolo"},
            {"◦",  "vuoto"},     {"⁃",   "trattino"},    {"▸",  "play piccolo"},
            {"‒",  "fig."},      {"–",   "medio"},       {"—",  "lungo"},
            {"›",  "angolino"},  {"»",   "doppio ang."}, {"∙",  "centrato"},
        }},
        { "Frecce", {
            {"→",  "destra"},     {"←",  "sinistra"},   {"↑",  "su"},
            {"↓",  "giù"},        {"↔",  "doppia"},      {"⇒",  "implica"},
            {"⟹", "impl. lungo"},{"➤",  "piena"},       {"➜",  "curva"},
            {"➝",  "fine"},       {"➔",  "bold"},        {"➙",  "aperta"},
            {"↳",  "sub"},        {"↩",  "ritorno"},     {"↪",  "redirect"},
            {"▶",  "play"},       {"◀",  "back"},        {"⬆",  "su piena"},
            {"⬇",  "giù piena"},  {"⬅",  "sx piena"},   {"➡",  "dx piena"},
        }},
        { "Geometrici pieni", {
            {"●",  "cerchio"},    {"■",  "quadrato"},    {"▲",  "triang. su"},
            {"▼",  "triang. giù"},{"◆",  "rombo"},       {"◉",  "mirino"},
            {"⬤",  "cerchio gr."},{"⬛",  "quadr. gr."},  {"▮",  "rettang."},
            {"◼",  "quadr. med."},{"⬥",  "rombo pic."},  {"◘",  "inverso"},
            {"◙",  "cerchio sq."}, {"◗", "semiluna"},
        }},
        { "Geometrici vuoti", {
            {"○",  "cerchio"},    {"□",  "quadrato"},    {"△",  "triang."},
            {"▽",  "triang. inv."},{"◇", "rombo"},       {"▷",  "play vuoto"},
            {"◎",  "doppio"},     {"⬜",  "quadr. gr."},  {"◻",  "quadr. med."},
            {"⟡",  "rombo punt."}, {"⊙", "cerchio +"},  {"⊚",  "cerchio ○"},
            {"⊛",  "cerchio *"},  {"⊜",  "cerchio ="},
        }},
        { "Check e stato", {
            {"✓",  "check"},      {"✔",  "check bold"},  {"✗",  "x"},
            {"✘",  "x bold"},     {"☑",  "check box"},   {"☒",  "x box"},
            {"☐",  "box vuoto"},  {"✅",  "ok emoji"},    {"❌",  "x emoji"},
            {"⚠",  "warning"},    {"🚫",  "divieto"},     {"ℹ",  "info"},
            {"⛔",  "stop"},       {"❗",  "!"},           {"❕",  "! vuoto"},
            {"❓",  "?"},          {"❔",  "? vuoto"},     {"💡",  "idea"},
        }},
        { "Stelle e enfasi", {
            {"★",  "stella"},     {"☆",  "stella vuo."}, {"✦",  "4 punte"},
            {"✧",  "4 punte vuo."},{"✨", "sparkle"},    {"⭐",  "star emoji"},
            {"❤",  "cuore"},      {"♦",  "quadro"},      {"◈",  "rombo punt."},
            {"❖",  "rombo nero"}, {"⁕",  "asterisco"},   {"※",  "refer."},
            {"✺",  "asterisco cr."},{"✼","asterisco gr."}, {"❋", "fiore"},
            {"🌟",  "glow"},      {"💫",  "star fly"},    {"☀",  "sole"},
        }},
        { "Numerici cerchiati", {
            {"①",  "1"},  {"②",  "2"},  {"③",  "3"},  {"④",  "4"},  {"⑤",  "5"},
            {"⑥",  "6"},  {"⑦",  "7"},  {"⑧",  "8"},  {"⑨",  "9"},  {"⑩",  "10"},
            {"❶",  "1 B"}, {"❷", "2 B"}, {"❸", "3 B"}, {"❹", "4 B"}, {"❺", "5 B"},
            {"➊",  "1 N"}, {"➋", "2 N"}, {"➌", "3 N"}, {"➍", "4 N"}, {"➎", "5 N"},
        }},
        { "Separatori e linee", {
            {"│",  "vert."},      {"┃",  "vert. bold"},  {"┄",  "tratteg."},
            {"═",  "doppia"},     {"║",  "doppia vert."}, {"━",  "bold"},
            {"─",  "sottile"},    {"〰", "ondulata"},     {"∽",  "simile"},
            {"≈",  "circa"},      {"·····","puntini"},    {"• • •","spaz."},
            {"┼",  "croce"},      {"╋",  "croce bold"},  {"╌",  "tratteg. 2"},
        }},
        { "Citazioni e testo", {
            {"«",  "apri «»"},    {"»",  "chiudi «»"},   {"‹",  "apri ‹›"},
            {"›",  "chiudi ‹›"},  {"\u201C","apri " ""},  {"\u201D","chiudi " ""},
            {"\u2018","apri ' '"},{"\u2019","chiudi ' '"},{"…",  "puntini"},
            {"‼",  "!! doppio"},  {"⁉",  "?!"},          {"‽",  "interrobang"},
            {"¿",  "? inv."},     {"¡",  "! inv."},      {"″",  "bis"},
        }},
        { "Simboli tipografici", {
            {"©",  "copyright"},  {"®",  "registered"},  {"™",  "trademark"},
            {"°",  "gradi"},      {"§",  "paragrafo"},   {"¶",  "pilcrow"},
            {"†",  "croce"},      {"‡",  "croce dop."},  {"∞",  "infinito"},
            {"≠",  "diverso"},    {"±",  "±"},            {"×",  "per"},
            {"÷",  "diviso"},     {"∴",  "quindi"},      {"∵",  "perché"},
            {"≤",  "≤"},          {"≥",  "≥"},            {"≡",  "identico"},
            {"#",  "hashtag"},    {"@",  "at"},           {"&",  "e commer."},
        }},
        { "Mani e gesti", {
            {"👉",  "→ destra"},  {"👈",  "← sinistra"}, {"👆",  "↑ su"},
            {"👇",  "↓ giù"},     {"👍",  "like"},        {"👎",  "dislike"},
            {"🙌",  "evviva"},    {"💪",  "forza"},       {"✍",   "scrittura"},
            {"🤝",  "handshake"},{"🖐",  "mano aperta"}, {"✌",   "vittoria"},
            {"🤞",  "dita incr."},{"👏",  "applauso"},   {"🫵",  "punta tu"},
        }},
        { "Decorativi colorati", {
            {"🔹",  "rombo blu"},  {"🔸",  "rombo arancio"},{"🔺",  "triang. rosso"},
            {"🔻",  "triang. giù"},{"🔷",  "rombo blu gr."},{"🔶",  "rombo arancio gr."},
            {"💠",  "diamante"},   {"🟢",  "verde"},         {"🟡",  "giallo"},
            {"🔴",  "rosso"},      {"🟣",  "viola"},         {"⚫",   "nero"},
            {"🔵",  "blu"},        {"🟤",  "marrone"},       {"⚪",   "bianco"},
        }},
    };
}

// ═══════════════════════════════════════════════════════════════════════════
//  MainWindow
// ═══════════════════════════════════════════════════════════════════════════

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    buildData();
    buildUi();
}

void MainWindow::buildUi()
{
    setWindowTitle("Symbol Picker");
    resize(760, 620);

    // Widget centrale
    auto *central = new QWidget(this);
    setCentralWidget(central);

    auto *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(12, 12, 12, 8);
    mainLayout->setSpacing(8);

    // ── Barra di ricerca ──────────────────────────────────────────────────
    m_search = new QLineEdit(this);
    m_search->setPlaceholderText("🔍  Cerca simbolo o categoria…");
    m_search->setClearButtonEnabled(true);
    m_search->setFixedHeight(34);
    m_search->setStyleSheet(
        "QLineEdit {"
        "  border:1px solid palette(mid);"
        "  border-radius:6px;"
        "  padding:0 10px;"
        "  font-size:13px;"
        "}"
        "QLineEdit:focus {"
        "  border-color:palette(highlight);"
        "}");
    connect(m_search, &QLineEdit::textChanged,
            this,     &MainWindow::rebuildContent);
    mainLayout->addWidget(m_search);

    // ── Scroll area ───────────────────────────────────────────────────────
    auto *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->verticalScrollBar()->setSingleStep(20);

    m_container = new QWidget();
    m_containerLayout = new QVBoxLayout(m_container);
    m_containerLayout->setContentsMargins(4, 4, 4, 16);
    m_containerLayout->setSpacing(0);
    scroll->setWidget(m_container);
    mainLayout->addWidget(scroll, 1);

    // ── Toast ─────────────────────────────────────────────────────────────
    m_toast = new QLabel(this);
    m_toast->setAlignment(Qt::AlignCenter);
    m_toast->setFixedHeight(28);
    m_toast->setStyleSheet(
        "QLabel {"
        "  background:#333;"
        "  color:#fff;"
        "  border-radius:14px;"
        "  font-size:12px;"
        "  padding:0 14px;"
        "}");
    m_toast->hide();
    m_toastTimer = new QTimer(this);
    m_toastTimer->setSingleShot(true);
    connect(m_toastTimer, &QTimer::timeout, m_toast, &QLabel::hide);

    // ── Contenuto iniziale ────────────────────────────────────────────────
    rebuildContent();
}

void MainWindow::rebuildContent(const QString &filter)
{
    // Elimina tutti i widget precedenti
    while (QLayoutItem *item = m_containerLayout->takeAt(0)) {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }

    const QString f = filter.trimmed().toLower();
    bool anyVisible = false;

    for (const Category &cat : std::as_const(m_data)) {

        // Filtra gli item
        QVector<SymbolItem> visible;
        if (f.isEmpty()) {
            visible = cat.items;
        } else {
            // mostra tutta la categoria se il nome fa match
            bool catMatch = cat.name.toLower().contains(f);
            for (const SymbolItem &si : cat.items) {
                if (catMatch ||
                    si.sym.contains(f) ||
                    si.label.toLower().contains(f))
                    visible.append(si);
            }
        }
        if (visible.isEmpty())
            continue;

        anyVisible = true;

        // ── Titolo categoria ──────────────────────────────────────────────
        auto *catLabel = new QLabel(cat.name.toUpper(), m_container);
        catLabel->setStyleSheet(
            QString("color:%1;")
                .arg(cssColor(palette().color(QPalette::Text).lighter(135))) +
            "font-size:11px;"
            "font-weight:bold;"
            "letter-spacing:0.08em;"
            "margin-top:14px;"
            "margin-bottom:4px;");
        m_containerLayout->addWidget(catLabel);

        // ── Separatore sottile ────────────────────────────────────────────
        auto *line = new QFrame(m_container);
        line->setFrameShape(QFrame::HLine);
        line->setFixedHeight(1);
        line->setStyleSheet(
            QString("background:%1;")
                .arg(cssColor(palette().color(QPalette::Mid))));
        m_containerLayout->addWidget(line);

        // ── Flow layout con i chip ────────────────────────────────────────
        auto *flowWidget = new QWidget(m_container);
        auto *flow       = new FlowLayout(flowWidget, /*margin*/4, /*hSpace*/6, /*vSpace*/6);
        flowWidget->setLayout(flow);

        for (const SymbolItem &si : std::as_const(visible)) {
            auto *chip = new SymbolChip(si.sym, si.label, flowWidget);
            chip->onClicked = [this](const QString &sym, const QString &lbl) {
                QApplication::clipboard()->setText(sym);
                showToast(QString("✓  Copiato:  %1  (%2)").arg(sym, lbl));
            };
            flow->addWidget(chip);
        }

        m_containerLayout->addWidget(flowWidget);
    }

    if (!anyVisible) {
        auto *noRes = new QLabel("Nessun risultato trovato.", m_container);
        noRes->setAlignment(Qt::AlignCenter);
        noRes->setStyleSheet(
            QString("color:%1; font-size:14px; margin:40px;")
                .arg(cssColor(palette().color(QPalette::Text).lighter(125))));
        m_containerLayout->addWidget(noRes);
    }

    m_containerLayout->addStretch();
}

void MainWindow::showToast(const QString &msg)
{
    m_toast->setText(msg);
    // centra il toast in basso
    const int tw = qMin(400, width() - 40);
    m_toast->setFixedWidth(tw);
    m_toast->move((width() - tw) / 2, height() - 52);
    m_toast->raise();
    m_toast->show();
    m_toastTimer->start(1600);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (m_toast && m_toast->isVisible()) {
        const int tw = m_toast->width();
        m_toast->move((width() - tw) / 2, height() - 52);
    }
}
