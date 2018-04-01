#include <cc/ui/Application>
#include <cc/ui/StylePlugin>
#include <cc/ui/Label>
#include <cc/ui/RowLayout>
#include <qh/CodeSnippet>

using namespace cc;
using namespace cc::ui;
using namespace qh;

class MainView: public View
{
    friend class Object;

    MainView()
    {
        size = Size{640, 480};
        color = Color{"#FFFFFF"};

        View *box = View::create(this);
        box->color = Color{"#F0F0F0"};
        box->centerInParent();

        RowLayout::setup(box);

        CodeSnippet::create(box,
            "int main(int argc, char **argv)\n"
            "{\n"
            "   printf(\"Hello, world!\\n\");\n"
            "   return 0;\n"
            "}"
        );
    }

    bool hasKeyInput() const { return true; }

    bool onKeyPressed(const KeyEvent *event)
    {
        if (+(event->modifiers() & KeyModifier::Control))
        {
            if (event->keyCode() == '+')
                Application::instance()->textZoom += 4;
            else if (event->keyCode() == '-')
                Application::instance()->textZoom -= 4;
        }

        return true;
    }
};

int main(int argc, char **argv)
{
    Application *app = Application::open(argc, argv);
    // app->textZoom = 20;
    Window::open(Object::create<MainView>(), "Hello, world!");
    return app->run();
}
