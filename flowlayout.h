#pragma once
// FlowLayout - dispone i widget in righe, va a capo automaticamente.
// Adattato dall'esempio ufficiale Qt (BSD-3-Clause).

#include <QLayout>
#include <QRect>
#include <QStyle>

class FlowLayout : public QLayout
{
public:
    explicit FlowLayout(QWidget *parent, int margin = 0, int hSpacing = 6, int vSpacing = 6);
    explicit FlowLayout(int margin = 0, int hSpacing = 6, int vSpacing = 6);
    ~FlowLayout() override;

    void addItem(QLayoutItem *item) override;
    int  horizontalSpacing() const;
    int  verticalSpacing()   const;

    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth()          const override;
    int  heightForWidth(int w)        const override;
    int  count()                      const override;
    QLayoutItem *itemAt(int index)    const override;
    QLayoutItem *takeAt(int index)          override;
    QSize minimumSize()               const override;
    QSize sizeHint()                  const override;
    void  setGeometry(const QRect &r)       override;

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm)        const;

    QList<QLayoutItem *> m_items;
    int m_hSpace;
    int m_vSpace;
};
