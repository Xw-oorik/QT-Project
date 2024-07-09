#ifndef JSONHIGHLIGHTER_H
#define JSONHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegularExpression>
class JsonHighlighter: public QSyntaxHighlighter
{
    Q_OBJECT
public:
    JsonHighlighter(QTextDocument* parent);
private:
    struct HighlightingRule {
        QRegularExpression pattern;  // 匹配模式
        QTextCharFormat format;      // 格式
    };
    QList<HighlightingRule> highlightingRules;

    QTextCharFormat keyFormat;     // 键
    QTextCharFormat stringFormat;  // 字符串
    QTextCharFormat numberFormat;  // 数字
    QTextCharFormat boolFormat;    // 布尔
    QTextCharFormat nullFormat;    // 空值
protected:
    void highlightBlock(const QString &text) override;
};

#endif // JSONHIGHLIGHTER_H
