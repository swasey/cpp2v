/*
 * Copyright (C) BedRock Systems Inc. 2019 Gregory Malecha
 *
 * SPDX-License-Identifier:AGPL-3.0-or-later
 */
#include "Formatter.hpp"
#include "llvm/ADT/StringRef.h"

class CoqPrinter {
public:
    CoqPrinter(fmt::Formatter& output) : output_(output) {}

    fmt::Formatter& begin_tuple() {
        return this->output_ << "(";
    }
    fmt::Formatter& end_tuple() {
        return this->output_ << ")";
    }
    fmt::Formatter& next_tuple() {
        return this->output_ << "," << fmt::nbsp;
    }

    fmt::Formatter& ctor(const char* ctor, bool line = true) {
        if (line) {
            this->output_ << fmt::line;
        }
        return this->output_ << fmt::lparen << ctor << fmt::nbsp;
    }
    fmt::Formatter& end_ctor() {
        return this->output_ << fmt::rparen;
    }
    fmt::Formatter& begin_record(bool line = true) {
        if (line) {
            this->output_ << fmt::line;
        }
        return this->output_ << "{|" << fmt::nbsp;
    }
    fmt::Formatter& end_record(bool line = true) {
        if (line) {
            this->output_ << fmt::line;
        }
        return this->output_ << fmt::nbsp << "|}";
    }
    fmt::Formatter& record_field(const char* field, bool line = true) {
        return this->output_ << field << fmt::nbsp << ":=" << fmt::nbsp;
    }

    fmt::Formatter& some() {
        return this->ctor("Some");
    }
    fmt::Formatter& none() {
        return this->output_ << "None";
    }

    fmt::Formatter& ascii(int c) {
        assert(0 <= c && c < 256);
        this->output_.ascii(c);
        return this->output_;
    }

    fmt::Formatter& str(const char* str) {
        return this->output_ << "\"" << str << "\"";
    }
    fmt::Formatter& str(llvm::StringRef str) {
        return this->output_ << "\"" << str << "\"";
    }

    fmt::Formatter& boolean(bool b) {
        return this->output_ << (b ? "true" : "false");
    }

    fmt::Formatter& begin_list() {
        return this->output_ << fmt::lparen;
    }
    fmt::Formatter& end_list() {
        return this->output_ << "nil" << fmt::rparen;
    }
    fmt::Formatter& cons() {
        return this->output_ << fmt::nbsp << "::" << fmt::nbsp;
    }

public:
    fmt::Formatter& output() {
        return this->output_;
    }

private:
    fmt::Formatter& output_;
};
