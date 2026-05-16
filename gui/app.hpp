#pragma once
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/combobox.h>
#include <wx/statline.h>
#include <wx/notebook.h>
#include <wx/spinctrl.h>
#include <string>
#include <format>
#include "../sequence/Sequence.hpp"
#include "../array_sequence/ArraySequence.hpp"
#include "../array_sequence/MutableArraySequence.hpp"
#include "../exceptions/Exceptions.hpp"
#include "../hanoi/HanoiTower.hpp"
#include "../stack/Stack.hpp"

class MyFrame : public wxFrame {
public:
    MyFrame();
    ~MyFrame();

private:
    // ВКЛАДКА STACK
    void on_create_stack(wxCommandEvent& event);
    void on_select_object(wxCommandEvent& event);
    void on_select_target(wxCommandEvent& event);
    void on_push(wxCommandEvent& event);
    void on_pop(wxCommandEvent& event);
    void on_get_length(wxCommandEvent& event);
    void on_substack(wxCommandEvent& event);
    void on_concat(wxCommandEvent& event);
    void on_clear(wxCommandEvent& event);

    void update_comboboxes();
    void show_stack();
    void update_current_length();
    void update_concat();
    void update_operations(const Stack<double, MutableArraySequence>& stack);
    void add_stack_to_list(const Stack<double, MutableArraySequence>& new_stack);
    bool get_input(wxTextCtrl* ctrl, double& value);

    Stack<double, MutableArraySequence>& get_active_stack();
    Stack<double, MutableArraySequence>& get_target_stack();
    
    size_t current_stack_id = 0;
    size_t max_elem_length = 4;
    MutableArraySequence<Stack<double, MutableArraySequence>> stacks;
    
    wxComboBox* object_selector;
    wxComboBox* target_selector;
    
    wxButton* button_clear;
    wxButton* button_pop;
    wxButton* button_substack;
    wxButton* button_concat;

    wxTextCtrl* input_value;
    wxTextCtrl* input_index;
    
    wxListBox* stack_list_box;

    wxStaticText* current_length;

    // ВКЛАДКА HANOI
    void on_hanoi_init(wxCommandEvent& event);
    void on_next_move(wxCommandEvent& event);
    void on_prev_move(wxCommandEvent& event);
    void on_hanoi_reset(wxCommandEvent& event);

    void show_hanoi();
    std::string draw_ring(const Ring& ring);

    HanoiTower<Ring> tower;
    MutableArraySequence<HanoiMove> moves;
    size_t current_move_id = 0;

    wxSpinCtrl* ring_counter;
    wxComboBox* start_selector;

    wxTextCtrl* first_rod_visual;
    wxTextCtrl* second_rod_visual;
    wxTextCtrl* third_rod_visual;

    wxStaticText* game_status;




};

int run_gui();
