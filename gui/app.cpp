#include "app.hpp"

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8("Лабораторная работа №3"), wxDefaultPosition, wxSize(1200, 800)) {

    wxNotebook* notebook = new wxNotebook(this, wxID_ANY);

    // ВКЛАДКА STACK
    wxPanel* stack_panel = new wxPanel(notebook);
    notebook->AddPage(stack_panel, wxString::FromUTF8("Стек"));

    Stack<double, MutableArraySequence> initial_stack;
    stacks.append(initial_stack);



    wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* left_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* active_title = new wxStaticText(stack_panel, wxID_ANY, wxString::FromUTF8("Активный стек:"));
    left_sizer->Add(active_title, 0, wxLEFT | wxTOP, 5);

    wxButton* button_create_stack = new wxButton(stack_panel, wxID_ANY, wxString::FromUTF8("New Stack"));
    button_create_stack->Bind(wxEVT_BUTTON, &MyFrame::on_create_stack, this);
    left_sizer->Add(button_create_stack, 0, wxEXPAND | wxALL, 5);

    object_selector = new wxComboBox(stack_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    object_selector->Bind(wxEVT_COMBOBOX, &MyFrame::on_select_object, this);

    left_sizer->Add(object_selector, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(stack_panel), 0, wxEXPAND | wxALL, 10);

    // Поля ввода для стека
    wxStaticText* value_title = new wxStaticText(stack_panel, wxID_ANY, wxString::FromUTF8("Значение (double):"));
    left_sizer->Add(value_title, 0, wxLEFT | wxTOP, 5);

    input_value = new wxTextCtrl(stack_panel, wxID_ANY, "");
    input_value->SetHint(wxString::FromUTF8("Например: 42.911"));
    left_sizer->Add(input_value, 0, wxEXPAND | wxALL, 5);

    wxStaticText* index_title = new wxStaticText(stack_panel, wxID_ANY, wxString::FromUTF8("Индексы start-end"));
    left_sizer->Add(index_title, 0, wxLEFT | wxTOP, 5);

    input_index = new wxTextCtrl(stack_panel, wxID_ANY, "");
    input_index->SetHint(wxString::FromUTF8("Например: 0-2"));
    left_sizer->Add(input_index, 0, wxEXPAND | wxALL, 5);



    // Сетка кнопок для стека
    wxGridSizer* button_grid = new wxGridSizer(3, 2, 5, 5);

    wxButton* button_push = new wxButton(stack_panel, wxID_ANY, "Push");
    button_push->Bind(wxEVT_BUTTON, &MyFrame::on_push, this);
    button_grid->Add(button_push, 1, wxEXPAND);

    wxButton* button_pop = new wxButton(stack_panel, wxID_ANY, "Pop");
    button_pop->Bind(wxEVT_BUTTON, &MyFrame::on_pop, this);
    button_grid->Add(button_pop, 1, wxEXPAND);

    wxButton* button_gl = new wxButton(stack_panel, wxID_ANY, "Get Length");
    button_gl->Bind(wxEVT_BUTTON, &MyFrame::on_get_length, this);
    button_grid->Add(button_gl, 1, wxEXPAND);

    wxButton* button_clear = new wxButton(stack_panel, wxID_ANY, "Clear");
    button_clear->Bind(wxEVT_BUTTON, &MyFrame::on_clear, this);
    button_grid->Add(button_clear, 1, wxEXPAND);

    wxButton* button_substack = new wxButton(stack_panel, wxID_ANY, "SubStack");
    button_substack->Bind(wxEVT_BUTTON, &MyFrame::on_substack, this);
    button_grid->Add(button_substack, 1, wxEXPAND);

    wxButton* button_concat = new wxButton(stack_panel, wxID_ANY, "Concat");
    button_concat->Bind(wxEVT_BUTTON, &MyFrame::on_concat, this);
    button_grid->Add(button_concat, 1, wxEXPAND);

    left_sizer->Add(button_grid, 0, wxEXPAND | wxALL, 5);
    left_sizer->Add(new wxStaticLine(stack_panel), 0, wxEXPAND | wxALL, 10);

    // Выбор целевого стека
    wxStaticText* target_title = new wxStaticText(stack_panel, wxID_ANY, wxString::FromUTF8("Целевой стек (для Concat):"));
    left_sizer->Add(target_title, 0, wxLEFT | wxTOP, 5);
    
    target_selector = new wxComboBox(stack_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    left_sizer->Add(target_selector, 0, wxEXPAND | wxALL, 5);

    left_sizer->AddStretchSpacer();

    main_sizer->Add(left_sizer, 0, wxEXPAND | wxALL, 10);

    // Листбокс для вывода стека
    stack_list_box = new wxListBox(stack_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_SINGLE | wxHSCROLL);
    stack_list_box->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    
    main_sizer->Add(stack_list_box, 1, wxEXPAND | wxALL, 10);

    stack_panel->SetSizer(main_sizer);
    
    update_comboboxes();
    show_stack();
    Centre();
}

MyFrame::~MyFrame() {}


void MyFrame::update_comboboxes() {
    int active_index = object_selector->GetSelection();
    int target_index = target_selector->GetSelection();

    object_selector->Clear();
    target_selector->Clear();

    size_t count = stacks.get_length();

    for (size_t number = 0; number < count; ++number) {
        wxString name = wxString::Format(wxString::FromUTF8("Stack №%zu"), number + 1);
        object_selector->Append(name);
        target_selector->Append(name);
    }

    if (active_index < count) {
        object_selector->SetSelection(active_index);
        current_stack_id = active_index;
    } else {
        object_selector->SetSelection(0);
        current_stack_id = 0;
    }

    target_selector->SetSelection(target_index);
}

void MyFrame::show_stack() {
    stack_list_box->Clear();

    Stack<double, MutableArraySequence>& stack = get_active_stack();
    
    if (stack.is_empty()) {
        stack_list_box->Append(wxString::FromUTF8("Здесь могла бы быть реклама отечественного аналога Гитхаба"));
    } else {
        MutableArraySequence<double> items;
        for (auto it = stack.begin(); it != stack.end(); ++it) {
            items.append(*it);
        }
        
        for (size_t counter = items.get_length(); counter > 0; --counter) {
            double value = items.get(counter - 1);
            wxString item_string = wxString::Format("|  %.2f  |", value); 
            stack_list_box->Append(item_string);
        }
    }
}


void MyFrame::add_stack_to_list(const Stack<double, MutableArraySequence>& new_stack) {
    stacks.append(new_stack);
    update_comboboxes();
    
    current_stack_id = stacks.get_length() - 1;
    object_selector->SetSelection(current_stack_id);
    
    show_stack();
}

Stack<double, MutableArraySequence>& MyFrame::get_active_stack() {
    if (current_stack_id >= stacks.get_length()) {
        throw IndexOutOfRangeException("MyFrame: get_active_stack. Стека с таким индексом нет.");
    }
    return stacks.get_reference(current_stack_id);
}

Stack<double, MutableArraySequence>& MyFrame::get_target_stack() {
    size_t id = target_selector->GetSelection();
    if (id >= stacks.get_length()) {
         return stacks.get_reference(0);
    }
    return stacks.get_reference(id);
}

bool MyFrame::get_input(wxTextCtrl* ctrl, double& value) {
    wxString value_inside = ctrl->GetValue();
    if (value_inside.IsEmpty()) {
        return false;
    }
    if (!value_inside.ToDouble(&value)) return false;
    return true;
}


void MyFrame::on_create_stack(wxCommandEvent& event) {
    Stack<double, MutableArraySequence> new_stack;
    stacks.append(new_stack);
    update_comboboxes();
    current_stack_id = stacks.get_length() - 1;
    object_selector->SetSelection(current_stack_id);
    show_stack();
}

void MyFrame::on_select_object(wxCommandEvent& event) {
    current_stack_id = object_selector->GetSelection();
    show_stack();
}

void MyFrame::on_push(wxCommandEvent& event) {
    double value;
    if (!get_input(input_value, value)) {
        wxMessageBox(wxString::FromUTF8("Введите корректное вещественное."), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
        return;
    }
    try {
        get_active_stack().push(value);
        show_stack();
        input_value->Clear();
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::on_pop(wxCommandEvent& event) {
    try {
        get_active_stack().pop();
        show_stack();
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::on_get_length(wxCommandEvent& event) {
    try {
        size_t length = get_active_stack().get_length();
        wxMessageBox(wxString::Format(wxString::FromUTF8("Длина: %zu"), length), wxString::FromUTF8("Информация"), wxOK | wxICON_INFORMATION);
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::on_clear(wxCommandEvent& event) {
    try {
        get_active_stack() = Stack<double, MutableArraySequence>();
        show_stack();
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::on_concat(wxCommandEvent& event) {
    size_t first_id = current_stack_id;
    size_t second_id = target_selector->GetSelection();

    if (first_id == second_id) {
        wxMessageBox(wxString::FromUTF8("Выберите разные стеки для конкатенации."), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
        return;
    }
    try {
        Stack<double, MutableArraySequence>& first_stack = stacks.get_reference(first_id);
        Stack<double, MutableArraySequence>& second_stack = stacks.get_reference(second_id);

        Stack<double, MutableArraySequence> result = first_stack.concat(second_stack);
        
        add_stack_to_list(result);
        
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::on_substack(wxCommandEvent& event) {
    wxString range = input_index->GetValue();
    int separator_pos = range.Find('-');

    if (separator_pos == wxNOT_FOUND) {
        wxMessageBox(wxString::FromUTF8("Формат: start-end (например, 0-2)"), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
        return;
    }

    int start, end;
    if (!range.Left(separator_pos).ToInt(&start) || !range.Mid(separator_pos + 1).ToInt(&end)) {
        wxMessageBox(wxString::FromUTF8("Неверные индексы"), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
        return;
    }
    
    try {
        Stack<double, MutableArraySequence> sub = get_active_stack().get_substack(static_cast<size_t>(start), static_cast<size_t>(end));
        add_stack_to_list(sub);
        
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}