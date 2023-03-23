#include "Browser.h"

Browser::Browser()
{
    windows.append(Window());
}

void Browser::newWindow()
{
    // TODO
    windows.prepend(Window());
}

void Browser::closeWindow()
{
    // TODO
    if (!windows.isEmpty())
    {
        windows.removeNodeAtIndex(0);
    }
}

void Browser::switchToWindow(int index)
{
    // TODO
    if (index <= windows.getSize() - 1 && index >= 0)
    {
        windows.moveToIndex(index, 0);
    }
}

Window &
Browser::getWindow(int index)
{
    return windows.getNodeAtIndex(index)->data;
}

void Browser::moveTab(Window &from, Window &to)
{
    // TODO
    to.newTab(from.getActiveTab());
    from.closeTab();
}

void Browser::mergeWindows(Window &window1, Window &window2)
{
    // TODO
    window2.changeActiveTabTo(0);
    while (!window2.isEmpty())
    {   
        window1.newTab(window2.getActiveTab());
        window2.closeTab();
    }
}

void Browser::mergeAllWindows()
{
    // TODO
    Window &first_window = windows.getFirstNode()->data;
    for (int i = 1; i < windows.getSize(); i++)
    {
        windows.getNodeAtIndex(i)->data.changeActiveTabTo(0);
        while (!windows.getNodeAtIndex(i)->data.isEmpty())
        {
            first_window.newTab(windows.getNodeAtIndex(i)->data.getActiveTab());
            windows.getNodeAtIndex(i)->data.closeTab();
        }
    }
}

void Browser::closeAllWindows()
{
    // TODO
    windows.removeAllNodes();
}

void Browser::closeEmptyWindows()
{
    // TODO
    int i = 0;
    while (i < windows.getSize())
    {
        
        if (windows.getNodeAtIndex(i)->data.isEmpty())
        {
            windows.removeNodeAtIndex(i);
            i--;
        }
        i++;
        if (windows.isEmpty())
        {
            break;
        }
    }
}

void Browser::print()
{
    Node<Window> *head = windows.getFirstNode();
    if (head == NULL)
    {
        std::cout << "The browser is empty" << std::endl;
    }
    else
    {
        (head->data).print();
        head = head->next;
        while (head != windows.getFirstNode())
        {
            (head->data).print();
            head = head->next;
        }
    }
}
