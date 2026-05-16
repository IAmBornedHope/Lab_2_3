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

    // Сетка кнопок для стека
    wxGridSizer* button_grid = new wxGridSizer(1, 2, 5, 5);

    wxButton* button_push = new wxButton(stack_panel, wxID_ANY, "Push");
    button_push->Bind(wxEVT_BUTTON, &MyFrame::on_push, this);
    button_grid->Add(button_push, 1, wxEXPAND);

    button_pop = new wxButton(stack_panel, wxID_ANY, "Pop");
    button_pop->Bind(wxEVT_BUTTON, &MyFrame::on_pop, this);
    button_grid->Add(button_pop, 1, wxEXPAND);


    left_sizer->Add(button_grid, 0, wxEXPAND | wxALL, 5);

    button_clear = new wxButton(stack_panel, wxID_ANY, "Clear");
    button_clear->Bind(wxEVT_BUTTON, &MyFrame::on_clear, this);
    left_sizer->Add(button_clear, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);


    left_sizer->Add(new wxStaticLine(stack_panel), 0, wxEXPAND | wxALL, 10);

    wxStaticText* index_title = new wxStaticText(stack_panel, wxID_ANY, wxString::FromUTF8("Индексы start-end"));
    left_sizer->Add(index_title, 0, wxLEFT | wxTOP, 5);

    input_index = new wxTextCtrl(stack_panel, wxID_ANY, "");
    input_index->SetHint(wxString::FromUTF8("Например: 0-2"));
    left_sizer->Add(input_index, 0, wxEXPAND | wxALL, 5);

    // Кнопка сабстека
    button_substack = new wxButton(stack_panel, wxID_ANY, "SubStack");
    button_substack->Bind(wxEVT_BUTTON, &MyFrame::on_substack, this);
    left_sizer->Add(button_substack, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    left_sizer->Add(new wxStaticLine(stack_panel), 0, wxEXPAND | wxALL, 10);

    // Выбор целевого стека
    wxStaticText* target_title = new wxStaticText(stack_panel, wxID_ANY, wxString::FromUTF8("Целевой стек:"));
    left_sizer->Add(target_title, 0, wxLEFT | wxTOP, 5);
    
    target_selector = new wxComboBox(stack_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    target_selector->Bind(wxEVT_COMBOBOX, &MyFrame::on_select_target, this);
    left_sizer->Add(target_selector, 0, wxEXPAND | wxALL, 5);

    // Кнопка конкатенации
    button_concat = new wxButton(stack_panel, wxID_ANY, "Concat");
    button_concat->Bind(wxEVT_BUTTON, &MyFrame::on_concat, this);
    left_sizer->Add(button_concat, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    left_sizer->Add(new wxStaticLine(stack_panel), 0, wxEXPAND | wxALL, 10);
    // Длина активного стека
    current_length = new wxStaticText(stack_panel, wxID_ANY, wxString::FromUTF8("Длина стека: 0"));
    left_sizer->Add(current_length, 0, wxLEFT | wxTOP, 5);

    left_sizer->AddStretchSpacer();

    main_sizer->Add(left_sizer, 0, wxEXPAND | wxALL, 10);

    // Листбокс для вывода стека
    stack_list_box = new wxListBox(stack_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_SINGLE | wxHSCROLL);
    stack_list_box->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Consolas"));
    
    main_sizer->Add(stack_list_box, 1, wxEXPAND | wxALL, 10);

    stack_panel->SetSizer(main_sizer);
    
    // ВКЛАДКА ХАНОЙСКОЙ БАШНИ
    wxPanel* hanoi_panel = new wxPanel(notebook);
    notebook->AddPage(hanoi_panel, wxString::FromUTF8("Ханой"));

    wxBoxSizer* hanoi_main_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hanoi_settings_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hanoi_move_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hanoi_rods_sizer = new wxBoxSizer(wxHORIZONTAL);

    hanoi_settings_sizer->Add(new wxStaticText(hanoi_panel, wxID_ANY, wxString::FromUTF8("Количество колец:")), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    ring_counter = new wxSpinCtrl(hanoi_panel, wxID_ANY, wxT("3"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 3, 12, 3);
    hanoi_settings_sizer->Add(ring_counter, 0, wxRIGHT, 15);
    hanoi_settings_sizer->Add(new wxStaticText(hanoi_panel, wxID_ANY, wxString::FromUTF8("Начальный стержень:")), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

    start_selector = new wxComboBox(hanoi_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    start_selector->AppendString(wxString::FromUTF8("1"));
    start_selector->AppendString(wxString::FromUTF8("2"));
    start_selector->AppendString(wxString::FromUTF8("3"));
    start_selector->SetSelection(0);
    hanoi_settings_sizer->Add(start_selector, 0, wxRIGHT, 15);

    // Управление стартом задачки и ходами
    wxButton* button_start = new wxButton(hanoi_panel, wxID_ANY, wxString::FromUTF8("Старт"));
    button_start->Bind(wxEVT_BUTTON, &MyFrame::on_hanoi_init, this);
    hanoi_settings_sizer->Add(button_start, 0, wxRIGHT, 10);

    hanoi_main_sizer->Add(hanoi_settings_sizer, 0, wxALL | wxCENTER, 10);
    hanoi_main_sizer->Add(new wxStaticLine(hanoi_panel), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    button_prev = new wxButton(hanoi_panel, wxID_ANY, wxString::FromUTF8("<- Назад"));
    button_prev->Bind(wxEVT_BUTTON, &MyFrame::on_prev_move, this);
    hanoi_move_sizer->Add(button_prev, 0, wxALL, 5);

    button_next = new wxButton(hanoi_panel, wxID_ANY, wxString::FromUTF8("Вперед ->"));
    button_next->Bind(wxEVT_BUTTON, &MyFrame::on_next_move, this);
    hanoi_move_sizer->Add(button_next, 0, wxALL, 5);

    // Управление авторежимом
    button_auto = new wxButton(hanoi_panel, wxID_ANY, wxString::FromUTF8("Авторежим"));
    button_auto->Bind(wxEVT_BUTTON, &MyFrame::on_hanoi_auto_mode, this);
    hanoi_move_sizer->Add(button_auto, 0, wxALL, 5);

    button_stop = new wxButton(hanoi_panel, wxID_ANY, wxString::FromUTF8("Стоп"));
    button_stop->Bind(wxEVT_BUTTON, &MyFrame::on_hanoi_stop, this);
    hanoi_move_sizer->Add(button_stop, 0, wxALL, 5);


    // Текущий ход
    game_status = new wxStaticText(hanoi_panel, wxID_ANY, wxString::FromUTF8("Ход: 0/0"));
    game_status->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    hanoi_move_sizer->Add(game_status, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 20);

    hanoi_main_sizer->Add(hanoi_move_sizer, 0, wxEXPAND | wxALL, 5);

    wxFont mono(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    first_rod_visual = new wxTextCtrl(hanoi_panel, wxID_ANY, "", wxDefaultPosition, wxSize(260, 350), wxTE_READONLY | wxTE_MULTILINE);
    first_rod_visual->SetFont(mono);
    first_rod_visual->SetBackgroundColour(wxColour(255, 255, 255));

    second_rod_visual = new wxTextCtrl(hanoi_panel, wxID_ANY, "", wxDefaultPosition, wxSize(260, 350), wxTE_READONLY | wxTE_MULTILINE);
    second_rod_visual->SetFont(mono);
    second_rod_visual->SetBackgroundColour(wxColour(255, 255, 255));

    third_rod_visual = new wxTextCtrl(hanoi_panel, wxID_ANY, "", wxDefaultPosition, wxSize(260, 350), wxTE_READONLY | wxTE_MULTILINE);
    third_rod_visual->SetFont(mono);
    third_rod_visual->SetBackgroundColour(wxColour(255, 255, 255));

    hanoi_rods_sizer->Add(first_rod_visual, 1, wxEXPAND | wxALL, 5);
    hanoi_rods_sizer->Add(second_rod_visual, 1, wxEXPAND | wxALL, 5);
    hanoi_rods_sizer->Add(third_rod_visual, 1, wxEXPAND | wxALL, 5);

    hanoi_main_sizer->Add(hanoi_rods_sizer, 1, wxEXPAND | wxALL, 10);
    hanoi_panel->SetSizer(hanoi_main_sizer);

    update_comboboxes();
    update_hanoi_buttons();
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
    max_elem_length = 4;
    Stack<double, MutableArraySequence>& stack = get_active_stack();
    
    update_current_length();
    update_operations(stack);
    update_concat();

    if (stack.is_empty()) {
        stack_list_box->Append(wxString::FromUTF8("Здесь могла бы быть реклама отечественного аналога Гитхаба"));
    } else {
        MutableArraySequence<double> items;
        for (const auto& item : stack) {
            wxString temp = wxString::Format(wxString::FromUTF8("%.2f"), item);
            if (temp.Length() > max_elem_length) {
                max_elem_length = temp.Length();
            }
            items.append(item);
        }

        
        for (size_t counter = items.get_length(); counter > 0; --counter) {
            double value = items.get(counter - 1);
            wxString item_string = wxString::Format(" [%03zu]  | %*.2f |", counter - 1, static_cast<int>(max_elem_length), value); 
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

void MyFrame::update_concat() {
    if (target_selector->GetSelection() == object_selector->GetSelection() || target_selector->GetSelection() == wxNOT_FOUND) {
        button_concat->Disable();
    } else {
        button_concat->Enable();
    }
}

void MyFrame::on_select_target(wxCommandEvent& event) {
    update_concat();
}

void MyFrame::update_operations(const Stack<double, MutableArraySequence>& stack) {
    if (stack.is_empty()) {
        button_clear->Disable();
        button_pop->Disable();
        button_substack->Disable();
    } else {
        button_clear->Enable();
        button_pop->Enable();
        button_substack->Enable();
    }
}

void MyFrame::on_push(wxCommandEvent& event) {
    double value;
    if (!get_input(input_value, value)) {
        wxMessageBox(wxString::FromUTF8("Введите корректное вещественное число."), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
        return;
    }
    try {
        get_active_stack().push(value);
        show_stack();
        input_value->SelectAll();
        input_value->SetFocus();
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::on_pop(wxCommandEvent& event) {
    try {
        get_active_stack().pop();
        show_stack();
        current_length->SetFocus();
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::update_current_length() {
    size_t length = get_active_stack().get_length();
    current_length->SetLabel(wxString::Format(wxString::FromUTF8("Длина стека: %zu"), length));
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
        input_value->Clear();
        input_index->Clear();
        current_length->SetFocus();
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

// ЛОГИКА ХАНОЙСКОЙ БАШНИ

std::string MyFrame::draw_ring(const Ring& ring) {
    const int WIDTH = 29;
    size_t size = ring.get_size();

    size_t ring_width = size * 2 + 1;
    size_t padding = (WIDTH - ring_width) / 2;
    std::string ring_string(ring_width, 'Z');
    std::string empty(padding, ' ');
    return std::format("{}{}{}", empty, ring_string, empty);

}

void MyFrame::update_hanoi_buttons() {
    size_t total_moves = moves.get_length();

    if (current_move_id < total_moves && !is_auto && total_moves != 0) {
        button_next->Enable();
    } else {
        button_next->Disable();
    }

    if ((current_move_id > 0 && !is_auto) && total_moves != 0) {
        button_prev->Enable();
    } else {
        button_prev->Disable();
    }

    if (total_moves != 0 && total_moves > 0 && !is_auto && current_move_id < total_moves) {
        button_auto->Enable();
    } else {
        button_auto->Disable();
    }

    if (is_auto && total_moves != 0) {
        button_stop->Enable();
    } else {
        button_stop->Disable();
    }

}

void MyFrame::show_hanoi() {
    const int EMPTY_LINES = 27;

    auto show_rod = [&](size_t rod_index, wxTextCtrl* ctrl) {
        Stack<Ring, MutableArraySequence>& rod = tower.get_rod(rod_index);
        MutableArraySequence<Ring> rings;
        for (const auto& ring : rod) {
            rings.append(ring);
        }

        size_t ring_count = rings.get_length();
        int free_space = EMPTY_LINES - ring_count;

        std::string temp_string(free_space, '\n');
        wxString place(temp_string);

        size_t length = rings.get_length();
        for (size_t index = length; index > 0; --index) {
            Ring ring = rings.get(index - 1); 
            place += wxString::FromUTF8(draw_ring(ring)) + "\n";
        }

        ctrl->SetValue(place);
    };

    show_rod(0, first_rod_visual);
    show_rod(1, second_rod_visual);
    show_rod(2, third_rod_visual);
    
    size_t total_moves = moves.get_length();
    game_status->SetLabel(wxString::Format(wxString::FromUTF8("Ход: %zu / %zu"), current_move_id, total_moves));
}

void MyFrame::on_hanoi_init(wxCommandEvent& event) {
    is_auto = false;
    size_t count = ring_counter->GetValue();
    size_t start_index = start_selector->GetSelection(); 

    MutableArraySequence<Ring> rings;
    
    for (size_t size = count; size >= 1; --size) {
        Color color = static_cast<Color>((size - 1) % 6);
        Shape shape = static_cast<Shape>((size - 1) % 3);
        rings.append(Ring(size, color, shape));
    }

    try {
        tower.initialize(rings, start_index);
        current_move_id = 0;
        const MutableArraySequence<HanoiMove>& all_moves = tower.get_moves();
        moves.clear();
        for (size_t index = 0; index < all_moves.get_length(); ++index) {
            moves.append(all_moves.get(index));
        }
        show_hanoi();
        update_hanoi_buttons();
        
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

void MyFrame::on_next_move(wxCommandEvent& event) {
    hanoi_next();
    update_hanoi_buttons();
    game_status->SetFocus();
}

void MyFrame::on_prev_move(wxCommandEvent& event) {
    if (current_move_id == 0) {
        wxMessageBox(wxString::FromUTF8("К сожалению, назад во времени ходить нельзя"), wxString::FromUTF8("Информация"), wxOK|wxICON_INFORMATION);
        return;
    }

    try {
        current_move_id--;
        HanoiMove hanoi_move = moves.get_reference(current_move_id);
        
        Stack<Ring, MutableArraySequence>& start = tower.get_rod(hanoi_move.end_rod);   
        Stack<Ring, MutableArraySequence>& end = tower.get_rod(hanoi_move.start_rod); 
        
        Ring ring = start.top();
        start.pop();
        end.push(ring);
        
        show_hanoi();
        update_hanoi_buttons();
        game_status->SetFocus();
        
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}


void MyFrame::on_hanoi_auto_mode(wxCommandEvent& event) {
    is_auto = true;
    update_hanoi_buttons();
    game_status->SetFocus();

    while (current_move_id < moves.get_length() && is_auto) {
        hanoi_next();
        game_status->SetFocus();
        wxYield();
        wxMilliSleep(450); 
    }

    is_auto = false;
    update_hanoi_buttons();
    game_status->SetFocus();
}

void MyFrame::on_hanoi_stop(wxCommandEvent& event) {
    is_auto = false;
    game_status->SetFocus();
}

void MyFrame::hanoi_next() {
    if (current_move_id >= moves.get_length()) {
        return;
    }
    try {

        HanoiMove hanoi_move = moves.get_reference(current_move_id);

        Stack<Ring, MutableArraySequence>& start = tower.get_rod(hanoi_move.start_rod);
        Stack<Ring, MutableArraySequence>& end = tower.get_rod(hanoi_move.end_rod);
        
        Ring ring = start.top();
        start.pop();
        end.push(ring);
        current_move_id++;
        show_hanoi();
    } catch (const Exception& error) {
        wxMessageBox(wxString::FromUTF8(error.what()), wxString::FromUTF8("Ошибка!"), wxOK | wxICON_ERROR);
    }
}

