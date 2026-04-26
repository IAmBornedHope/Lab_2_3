#pragma once
#include <wx/wx.h>
#include <string>
#include "../sequence/Sequence.hpp"
#include "../array_sequence/ArraySequence.hpp"
#include "../array_sequence/MutableArraySequence.hpp"
#include "../list_sequence/ListSequence.hpp"
#include "../exceptions/Exceptions.hpp" 

class MyFrame: public wxFrame {
public:
    MyFrame();
    ~MyFrame();
private:
    void on_select_object(wxCommandEvent& event);
    void on_append(wxCommandEvent& event);
    void on_prepend(wxCommandEvent& event);
    void on_insert_at(wxCommandEvent& event);
    void on_get_length(wxCommandEvent& event);
    void on_get_at(wxCommandEvent& event);
    void on_subsequence(wxCommandEvent& event);
    void on_concat(wxCommandEvent& event);
    void on_clear(wxCommandEvent& event);

    void refresh_output();
    Sequence<int>* get_sequence(size_t id);

    MutableArraySequence<int> array_1;
    MutableArraySequence<int> array_2;
    
};