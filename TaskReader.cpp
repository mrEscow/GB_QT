#include "TaskReader.h"

namespace
{
const QList<Task> mockDate {
    {"text","time","progress"},
    {"text1","time1","progress1"},
    {"text2","time2","progress2"}
};
}

std::pair<bool, QList<Task> > TaskReader::requestTaskBrowse()
{
    return std::make_pair(true,mockDate);
}
