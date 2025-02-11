#include "LocaleProperty.h"

#include <QDirIterator>
#include <QLocale>

#include "../editors/ComboEdit.h"

QList<QLocale> LocaleProperty::m_locales = QList<QLocale>();

LocaleProperty::LocaleProperty(const QString &name, QObject *propertyObject, QObject *parent) :
        Property(name, propertyObject, parent) {

    if(m_locales.isEmpty()) {
        QDirIterator it(":/Translations", QDirIterator::Subdirectories);
        while(it.hasNext()) {
            QFileInfo info(it.next());
            m_locales << QLocale(info.baseName());
        }
    }
}

QWidget *LocaleProperty::createEditor(QWidget *parent) const {
    ComboEdit *editor = new ComboEdit(parent);
    m_editor = editor;
    m_editor->setDisabled(isReadOnly());

    for(auto &it : m_locales) {
        QString name = QLocale(it).nativeLanguageName();
        editor->addItem(name.replace(0, 1, name[0].toUpper()), it);
    }

    connect(editor, &ComboEdit::currentIndexChanged, this, &LocaleProperty::valueChanged);
    return m_editor;
}

bool LocaleProperty::setEditorData(QWidget *editor, const QVariant &data) {
    ComboEdit *e = static_cast<ComboEdit *>(editor);
    if(e) {
        int index = e->findData(data.toLocale());
        if(index == -1) {
            return false;
        }
        e->blockSignals(true);
        e->setCurrentIndex(index);
        e->blockSignals(false);
        return true;
    }
    return Property::setEditorData(editor, data);
}

QVariant LocaleProperty::editorData(QWidget *editor) {
    ComboEdit *e = static_cast<ComboEdit *>(editor);
    if(e) {
        return QVariant::fromValue(QLocale(e->currentData().toString()));
    }
    return Property::editorData(editor);
}

void LocaleProperty::valueChanged() {
    ComboEdit *e = dynamic_cast<ComboEdit *>(m_editor);
    if(e) {
        setValue(e->currentData());
    }
}
