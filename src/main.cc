#include <cc/debug>
#include <cc/System>
#include <cc/Date>
#include <cc/ui/Application>
#include <cc/ui/SlideView>
#include <cc/ui/Transition>
#include <cc/ui/Column>
#include <cc/ui/Label>
#include <cc/ui/Transition>
#include <cc/ui/Timer>
#include <qh/CodeSnippet>

using namespace cc;
using namespace cc::ui;
using namespace qh;

class Slide1: public View
{
    friend class Object;

    Slide1(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        Column *box = Column::create(this);
        box->centerInParent();
        box->align = ColumnAlign::Center;
        Label::create(box, "Property Bindings in C++(>=11)", TextStyle::create(Font::select("Sans", 30 + Application::instance()->textZoom(), Weight::Bold)));
        Label::create(box, "<i>Frank Mertens &lt;frank@cyblogic.de&gt;</i>");
    }
};

class Slide2: public View
{
    friend class Object;

    Slide2(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        Label *label = Label::create(this, "MUC++", TextStyle::create(Font::select("Mono", 100 + Application::instance()->textZoom(), Weight::Bold)));
        label->centerInParent();

        easeOn(label->pos, 1, easing::outBounce);

        keyPressed->connect([=]{
            if (key()->scanCode() == ScanCode::Key_Space) {
                if (mapToGlobal(Point{}) != Point{}) return;
                if (!done_) {
                    label->pos->bind([=]{
                        return Point{
                            0.5 * (size()[0] - label->size()[0]),
                            size()[1] - label->size()[1]
                        };
                    });
                    done_ = true;
                }
                else {
                    label->centerInParent();
                    done_ = false;
                }
            }
        });
    }

    bool done_ { false };
};

class Slide3: public View
{
    friend class Object;

    Slide3(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        CodeSnippet::create(this,
            "keyPressed->connect([=]{\n"
            "    label->pos->bind([=]{\n"
            "        return Point{\n"
            "            0.5 * (size()[0] - label->size()[0]),\n"
            "            size()[1] - label->size()[1]\n"
            "        };\n"
            "    });\n"
            "});\n"
            "\n"
            "easeOn(label->pos, 1, easing::outBounce);\n"
        )->centerInParent();
    }
};

class Slide4: public View
{
    friend class Object;

    Slide4(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        Column *box = Column::create(this);
        box->color = Color{"#FFFFFF"};
        box->centerInParent();

        Label::create(box, "<b>HISTORY</b>");
        Label::create(box, "• explored by Olivier Goffart in 2013");
        Label::create(box, "• woboq.com/blog/property-bindings-in-cpp.html");
    }
};

class Slide5: public View
{
    friend class Object;

    Slide5(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        auto getClockText = []{
            Ref<const Date> date = Date::breakdown(System::now());
            return dec(date->hour(), 2) + "∶" + dec(date->minutes(), 2) + "∶" + dec(date->seconds(), 2);
        };

        Label *label = Label::create(this, getClockText());
        label->color = Color{"#D0D0FF"};
        label->centerInParent();

        easeOn(label->angle, 0.5, easing::Bezier(0.5, -0.4, 0.5, 1.4));

        keyPressed->connect([=]{
            if (key()->scanCode() == ScanCode::Key_Space) {
                if (mapToGlobal(Point{}) != Point{}) return;
                Timer::start(1, [=]{ label->text = getClockText(); label->angle += 45; });
            }
        });
    }
};

class Slide6: public View
{
    friend class Object;

    Slide6(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        CodeSnippet::create(this,
            "Label *label = Label::create(this, getClockText());\n"
            "label->color = Color{\"#D0D0FF\"};\n"
            "label->centerInParent();\n"
            "\n"
            "easeOn(label->angle, 0.5, easing::Bezier(0.5, -0.4, 0.5, 1.4));\n"
            "//...\n"
            "keyPressed->connect([=]{\n"
            "    Timer::start(1, [=]{\n"
            "        label->text = getClockText(); label->angle += 45;\n"
            "    });\n"
            "});\n"
        )->centerInParent();
    }
};

class Slide7: public View
{
    friend class Object;

    Slide7(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        Column *box = Column::create(this);
        box->color = Color{"#FFFFFF"};
        box->centerInParent();

        Label::create(box, "<b>PERFORMANCE</b>");
        Label::create(box, "• faster than QML if done right");
        Label::create(box, "• no JIT, no startup delay");
        Label::create(box, "• requires a good set API");

        CodeSnippet::create(box,
            "if ((activeInstance_) && (activeInstance_ != this)) {\n"
            "    if (activeInstance_->dependencies()->insert(this))\n"
            "        subscribers()->insert(activeInstance_);\n"
            "}\n"
        )->color = Color{"#E0E0E0"};
    }
};

class Slide8: public View
{
    friend class Object;

    Slide8(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        color = Color{"#FFFFFF"};

        Column *box = Column::create(this);
        box->color = Color{"#FFFFFF"};
        box->centerInParent();
        box->align = ColumnAlign::Center;

        Label::create(box, "<b>FIN</b>", TextStyle::create(Font::select("Sans", 30 + Application::instance()->textZoom(), Weight::Bold)));
        Label::create(box, "C++ source code of this presentation");
        Label::create(box, "<i>https://github.com/frankencode/ProperDemo</i>");
    }
};

class MainView: public SlideView
{
    friend class Object;

    MainView()
    {
        size = Size{1024, 768};

        Object::create<Slide1>(this);
        Object::create<Slide2>(this);
        Object::create<Slide3>(this);
        Object::create<Slide4>(this);
        Object::create<Slide5>(this);
        Object::create<Slide6>(this);
        Object::create<Slide7>(this);
        Object::create<Slide8>(this);

        easeOn(slideCarrier()->pos, 0.5, easing::Bezier(0.5, -0.4, 0.5, 1.4));

        keyPressed->connect([=]{
            if (key()->scanCode() == ScanCode::Key_Left) {
                currentIndex -= 1;
            }
            else if (key()->scanCode() == ScanCode::Key_Right) {
                currentIndex += 1;
            }
            else if ('0' <= +key()->keyCode() && +key()->keyCode() <= '9') {
                currentIndex = +key()->keyCode() - '1' + 10 * (+key()->keyCode() == '0');
            }
            else if (+(key()->modifiers() & KeyModifier::Control)) {
                if (key()->keyCode() == '+') {
                    Application::instance()->textZoom += 2;
                }
                else if (key()->keyCode() == '-') {
                    Application::instance()->textZoom -= 2;
                }
            }
        });
    }
};

int main(int argc, char **argv)
{
    Application *app = Application::open(argc, argv);
    app->textZoom = 10;
    Window::open(Object::create<MainView>(), "Hello, world!", WindowMode::Default|WindowMode::Accelerated);
    return app->run();
}
