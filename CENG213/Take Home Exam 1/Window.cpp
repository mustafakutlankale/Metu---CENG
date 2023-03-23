#include "Window.h"

Window::Window()
{
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab()
{
    // TODO
    int total_tabs = tabs.getSize();
    if (total_tabs == 0)
    {
        Tab empty_tab = Tab();
        return empty_tab;
    }
    else
    {
        return tabs.getNodeAtIndex(activeTab)->data;
    }
}

bool Window::isEmpty() const
{
    // TODO
    return tabs.isEmpty();
}

void Window::newTab(const Tab &tab)
{
    // TODO
    // Insert after activeTab
    if (activeTab != -1)
    {
        Node<Tab>* active_node = tabs.getNodeAtIndex(activeTab);
        tabs.insertAfterNode(tab, active_node);
        activeTab++;
    }
    else
    {
        tabs.append(tab);
        activeTab = 0;
    }
}

void Window::closeTab()
{
    // TODO
    if (tabs.getSize() == 0)
    {
        return;
    }

    if (tabs.getSize() == 1)
    {
        tabs.removeNodeAtIndex(activeTab);
        activeTab = -1;
    }

    else
    {
        if (activeTab == tabs.getSize() - 1)
        {   
            tabs.removeNodeAtIndex(activeTab);
            activeTab--;
        }
        else
        {
            tabs.removeNodeAtIndex(activeTab);
        }
    }
}

void Window::moveActiveTabTo(int index)
{
    // TODO
    if (activeTab == -1)
    {
        return;
    }
    if (activeTab == index)
    {
        return;
    }
    tabs.moveToIndex(activeTab, index);

    if (index < tabs.getSize() && index >= 0)
    {
        activeTab = index;
    }
    else
    {
        activeTab = tabs.getSize() - 1;
    }
}

void Window::changeActiveTabTo(int index)
{
    // TODO
    int tabs_left = tabs.getSize();
    if (index < tabs_left && index >= 0)
    {
        activeTab = index;
    }
}

void Window::addTab(Node<Tab> &tab)
{
    // TODO
    tabs.append(tab.data);
    if (activeTab == -1)
    {
        activeTab = 0;
    }
}

void Window::print()
{
    if (tabs.isEmpty())
        std::cout << "Window is empty" << std::endl;
    else
        std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
