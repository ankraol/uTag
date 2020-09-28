#include "EditPopupMenu.h"
#include "MultiTagEditor.h"

EditPopupMenu::EditPopupMenu(MultiTagEditor *multiTagEditor) : m_multiTagEditor(multiTagEditor) {
    m_editButton.set_label("Edit");

    m_editButton.signal_select().connect(sigc::mem_fun(*this, &EditPopupMenu::buttonPressed));
    add(m_editButton);
    show_all_children();
}

void EditPopupMenu::buttonPressed() {
    m_multiTagEditor->EditTags();
}
