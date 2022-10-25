/**********************************************************************************
// Item (Arquivo de Cabeçalho)
// 
// Criação:     14 Mai 2012
// Atualização: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define um item de menu
//
**********************************************************************************/

#ifndef _TRIALSMENU_ITEM_H_
#define _TRIALSMENU_ITEM_H_

// ---------------------------------------------------------------------------------

#include "Object.h"
#include "Animation.h"
#include "TileSet.h"
#include "Types.h"

// ---------------------------------------------------------------------------------

enum MenuState {SELECTED, NOTSELECTED};

// ---------------------------------------------------------------------------------

class Item : public Object
{
private:
    TileSet   * tileset;                // folha de sprites da animação
    Animation * animation;              // animação do menu
    
public:
    Item(float posX, float posY, float width, uint menuId, string imgFile, float height = 75.0f);
    ~Item();

    void Select();                      // seleciona menu
    void UnSelect();                    // desmarca seleção

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif