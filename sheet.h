#pragma once

#include <functional>
#include <unordered_map>

#include "cell.h"
#include "common.h"

class HasherCell {
public:
    size_t operator()(const Position p) const {
        return std::hash<std::string>()(p.ToString());
    }
};

class ComparatorCell {
public:
    bool operator()(const Position& lhs, const Position& rhs) const {
        return lhs == rhs;
    }
};

class Sheet : public SheetInterface {
public:
    using SheetTable = std::unordered_map<Position, std::unique_ptr<Cell>, HasherCell, ComparatorCell>;

    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

    const Cell* GetCellPtr(Position pos) const;
    Cell* GetCellPtr(Position pos);

private:
	SheetTable cells_;
};