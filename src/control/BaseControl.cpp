#include "BaseControl.h"

using namespace pisco::control;

BaseControl::BaseControl()
{

}

BaseControl::~BaseControl()
{

}

void BaseControl::setClassName(string name)
{
    m_class_name = name;
}