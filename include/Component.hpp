#ifndef TABLECOMPONENT_H
#define TABLECOMPONENT_H

namespace dmf {

namespace table {

enum class Align { LEFT, RIGHT, CENTER };
enum class HPolicy { MIN, SET_W, SEPARATOR };

class Component {
public:
    Component(const Align &alignment, const size_t &width)
        : alignment(alignment), width(width), separator(0)
    {
    }

    virtual void display() = 0;

    Align alignment;
    size_t width;
    size_t separator;

protected:
    static const char alignment_char(const Align &index)
    {
        static const char a[] = {'<', '>', '^'};
        return a[static_cast<int>(index)];
    }
};
} // namespace table
} // namespace dmf

#endif // !TABLECOMPONENT_H
