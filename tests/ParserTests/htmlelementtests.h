#include <QObject>
#include <QTest>

#include "htmlelement.h"

class HTMLElementTests : public QObject
{
    Q_OBJECT
    public:
        HTMLElementTests();

    private Q_SLOTS:
        void initTestCase();
        void cleanupTestCase();
        void testCreatingElements();
        void testCreatingElements_data();;

    private:
        HTMLElement *htmlElement;
};
