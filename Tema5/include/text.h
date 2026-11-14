#ifndef TEXT_H
#define TEXT_H

// =============================================================================
//  Item 14, varianta 3: COPIEREA RESURSEI (deep copy).
//  Când are sens să existe mai multe copii ale resursei (ex.: memorie cu text),
//  fiecare copie își alocă propria resursă.
// =============================================================================

class Text
{
public:
    explicit Text(const char* text);
    Text(const Text& other);              // deep copy
    Text& operator=(const Text& other);   // deep copy (ordine atentă, Item 11)
    ~Text();

    void afiseaza(const char* nume) const;

private:
    char* m_date;                         // resursa: memorie pe heap
};

#endif // TEXT_H