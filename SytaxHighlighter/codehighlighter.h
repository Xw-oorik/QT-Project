#ifndef CODEHIGHLIGHTER_H
#define CODEHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegularExpression>

class CodeHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    CodeHighlighter(QTextDocument* parent);
private:
    struct HighlightingRule {
        QRegularExpression pattern;  // 匹配模式
        QTextCharFormat format;      // 格式
    };
    QList<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat singleLineCommentFormat;

    QTextCharFormat multiLineCommentFormat;  // 多行注释
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
protected:
    void highlightBlock(const QString &text) override;
};

#endif // CODEHIGHLIGHTER_H
