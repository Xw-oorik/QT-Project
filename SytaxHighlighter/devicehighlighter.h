#ifndef DEVICEHIGHLIGHTER_H
#define DEVICEHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegularExpression>
class DeviceHighlighter: public QSyntaxHighlighter
{
    Q_OBJECT
public:
    DeviceHighlighter(QTextDocument* parent);
private:
    struct HighlightingRule {
        QRegularExpression pattern;  // 匹配模式
        QTextCharFormat format;      // 格式
    };
    QList<HighlightingRule> highlightingRules;
    QTextCharFormat timeFormat;       // 时间戳
    QTextCharFormat tempKeyFormat;    // 温度key
    QTextCharFormat tempValueFormat;  // 温度value
    QTextCharFormat humiKeyFormat;    // 湿度key
    QTextCharFormat humiValueFormat;  // 湿度value
    QTextCharFormat normalFormat;  // 正常
    QTextCharFormat lowerFormat;   // 偏低
    QTextCharFormat upperFormat;   // 偏高
protected:
    void highlightBlock(const QString &text) override;
};

#endif // DEVICEHIGHLIGHTER_H
