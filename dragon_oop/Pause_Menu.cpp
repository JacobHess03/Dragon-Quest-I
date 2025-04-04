#include "Pause_Menu.h"
#include "SpriteFactory.h"
#include "View.h"
#include "Game.h"
#include "Window.h"
#include "Audio.h"
#include <iostream>
#include"Menu.h"
#include "Dialogue_Menu.h"


using namespace agp;

Pause_MenuItem::Pause_MenuItem(int row, int col, Pause_Menu* container, const std::string& text, std::function<void()> task)
	: RenderableObject(container,
		RectF(
			container->menuRect().left() + 0.5f + 6 * (col - 1),
			container->menuRect().top() + 0.5f + 0.7f * (row - 1),
			container->menuRect().size.x / (container->getCols())+3, 0.5f),
		SpriteFactory::instance()->getText(' ' + text, { 0.5f, 0.5f }, 0, ' ', false))
{
	_container = container;
	_text = text;
	_task = task;
	_selected = false;
	_focusColor = { 255, 255, 255, 128 };
}

void Pause_MenuItem::refresh()
{
	setSprite(SpriteFactory::instance()->getText(' ' + _text, { 0.5f + _selected / 30.0f, 0.5f + _selected / 30.0f }, 0, ' ', _selected));
}

void Pause_MenuItem::update(float dt)
{
	RenderableObject::update(dt);

	//_focused = _selected;
}

Pause_Menu::Pause_Menu(int cols, int rows, const PointF& position, float width, Pause_Menu* parent, bool closable)
	: UIScene(RectF(0, 0, 16, 15))
{
	_rows = rows;
	_cols = cols;
	_parent = parent;
	_rowSelected = 0;
	_colSelected = 0;
	_menuRect = { position.x, position.y, width, 0.5f };
	_closable = closable;
	_items.resize(_rows, std::vector<Pause_MenuItem*>(_cols, nullptr));
	// menu layer
	_menuBackground = new RenderableObject(this, _menuRect, Color(0, 0, 0, 255));
	_menuBackground->setBorderColor({ 255, 255, 255, 255 });

	// default: modal menu (blocks all lower scenes)
	_blocking = true;
	
}

Pause_Menu::Pause_Menu(int rows,int cols,Pause_Menu* parent)
	: Pause_Menu(cols, rows, { parent->menuRect().left(),parent->menuRect().bottom()}, parent->menuRect().size.x, parent)
{
}

Pause_MenuItem* Pause_Menu::addItem(int col, int row, const std::string& text, std::function<void()> task)
{
	Pause_MenuItem* item = new Pause_MenuItem(row, col, this, text, task);
	if (row - 1 >= 0 && row - 1 < _items.size() && col - 1 >= 0 && col - 1 < _items[0].size())
		_items[row - 1][col - 1] = item;

	if (_items.size() == 1 && _items[0].size() == 1)
		item->setSelected(true);

	_menuRect.size.y = 0.5f + (_items.size()) * 0.7f + 0.3f;
	_menuRect.size.x = 0.5f + this->menuRect().size.x / _cols * _items[0].size();
	_menuBackground->setRect(_menuRect);

	return item;
}

void Pause_Menu::event(SDL_Event& evt)
{
	UIScene::event(evt);

	if (evt.type == SDL_KEYDOWN )
	{
		if (_items.size() > 1 || _items[0].size() > 1) {
			if (evt.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{

				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_rowSelected][_colSelected]->setSelected(false);
				_rowSelected = (_rowSelected + 1) % int(_items.size());
				_items[_rowSelected][_colSelected]->setSelected(true);

			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");

				_items[_rowSelected][_colSelected]->setSelected(false);
				_rowSelected = (_rowSelected - 1) < 0 ? int(_items.size()) - 1 : _rowSelected - 1;
				_items[_rowSelected][_colSelected]->setSelected(true);

			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_rowSelected][_colSelected]->setSelected(false);
				_colSelected = (_colSelected + 1) % int(_items[_rowSelected].size());
				_items[_rowSelected][_colSelected]->setSelected(true);

			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_rowSelected][_colSelected]->setSelected(false);
				_colSelected = (_colSelected - 1) < 0 ? int(_items[_rowSelected].size()) - 1 : _colSelected - 1;
				_items[_rowSelected][_colSelected]->setSelected(true);

			}

			else if (evt.key.keysym.scancode == SDL_SCANCODE_RETURN || evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
				_items[_rowSelected][_colSelected]->run();
			}
			/*else if (_closable && (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE || evt.key.keysym.scancode == SDL_SCANCODE_Z))
			{
				Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
				Game::instance()->popSceneLater();
				//Audio::instance()->resumeMusic();
			}*/
		}
		else {
			 if (evt.key.keysym.scancode == SDL_SCANCODE_RETURN || evt.key.keysym.scancode == SDL_SCANCODE_RIGHT){
				Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
				_items[_rowSelected][_colSelected]->run();
			}
			else if (_closable && (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE || evt.key.keysym.scancode == SDL_SCANCODE_Z))
			{
				Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
				Game::instance()->popSceneLater();
				Audio::instance()->resumeMusic();
			}
		}
	}
}

Pause_Menu* Pause_Menu::pauseMenu(Hero* hero)
{
	Pause_Menu* menu = new Pause_Menu(2, 3, { 1, 1 }, 8, 0, true);

	menu->addItem(1, 1, "Resume", []()
		{
			Game::instance()->popSceneLater();
			Audio::instance()->resumeMusic();
		});
	menu->addItem(2, 3, "Reset", []()
		{
			Game::instance()->reset();
		});
	menu->addItem(2, 1, "Quit", []() {Game::instance()->quit(); });
	menu->addItem(2, 2, "Items", [menu, hero]() {
		int i = 1;
		if (hero->getItems().size() > 0) {
			Pause_Menu* nestedmenu = new Pause_Menu(hero->getItems().size() + 1, 1, menu);
			for (auto item : hero->getItems()) {
				nestedmenu->addItem(1, i, item.second->getName(), [item, hero]() {
					Pause_Menu* decision_menu = new Pause_Menu(1, 3, { 1,12 }, 6, 0, true);
					decision_menu->addItem(1, 1, "Use", [item, hero]() {
						item.second->task();
						hero->removeItem(item.first);
						Game::instance()->popSceneLater();
						Game::instance()->popSceneLater();
						});
					decision_menu->addItem(1, 2, "Info",[decision_menu,item]() {
						decision_menu->infoItem(item.second);
						});
					decision_menu->addItem(1, 3, "Don't use", []() {
						Game::instance()->popSceneLater();
						});
					Game::instance()->pushScene(decision_menu);
					});
				i++;
			}
			nestedmenu->addItem(1, hero->getItems().size() + 1, "Back", []() {
				Game::instance()->popSceneLater();
				});
			Game::instance()->pushScene(nestedmenu);
		}
		else {
			std::vector<std::string> dialogue = { "You have no items!" };
			Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
		}
		});
	menu->addItem(1, 3, "Spell", [menu,hero]() {
		int i = 1;
		if (hero->getSpells().size() > 0) {
			Pause_Menu* nestedmenu = new Pause_Menu(hero->getSpells().size() + 1, 1, menu);
			for (auto spell : hero->getSpells()) {
				nestedmenu->addItem(1, i, spell.second->getName(), [spell, hero]() {
					Pause_Menu* decision_menu = new Pause_Menu(1, 3, { 1,12 }, 6, 0, true);
					decision_menu->addItem(1, 1, "Use", [spell, hero]() {
						if (spell.second->getName() == "Rage") {
							Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");
							std::vector<std::string> dialogue = { "You can only use it in battle!" };
							Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
						}
						else {
							if (spell.second->getCost() > hero->getMp())
								Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");
							else {
								spell.second->task();
								Game::instance()->popSceneLater();
								Game::instance()->popSceneLater();
							}
						}
						});
					decision_menu->addItem(1, 2, "Info", [decision_menu,spell]() {
						decision_menu->infoSpell(spell.second);
						});
					decision_menu->addItem(1, 3, "Don't use", []() {
						Game::instance()->popSceneLater();
						});
					Game::instance()->pushScene(decision_menu);
					});
				i++;
			}
			nestedmenu->addItem(1, hero->getSpells().size() + 1, "Back", []() {
				Game::instance()->popSceneLater();
				});
			Game::instance()->pushScene(nestedmenu);
		}
		else {
			std::vector<std::string> dialogue = { "You have no spells!" };
			Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
		}
		});
	menu->addItem(1, 2, "Status", [menu,hero]() {
		
			int i = 1;
			if (hero->getWeapons().size() > 0) {
				Pause_Menu* weaponmenu = new Pause_Menu(1, hero->getWeapons().size() + 1, { 1,4 }, 12, 0, true);
				//hud
				RectF _hud = { 11.5,11.5,4,3 };
				RenderableObject* _hudBackground = new RenderableObject(weaponmenu, _hud, Color(0, 0, 0, 255));
				_hudBackground->setBorderColor({ 255, 255, 255, 255 });
				new RenderableObject(weaponmenu, RectF(12.8, 11.7, 1.6, 1.6), SpriteFactory::instance()->getText("Hero", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(11.5, 12.2, 4, 0.05), Color(255, 255, 255, 255));
				new RenderableObject(weaponmenu, RectF(12.5, 12.7, 0.7, 0.5), SpriteFactory::instance()->getText(std::to_string(hero->getHp()), { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(11.6, 12.7, 0.5, 0.5), SpriteFactory::instance()->getText("Hp", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(12.1, 12.7, 0.5, 0.5), SpriteFactory::instance()->getText(":", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(13.5, 12.7, 0.5, 0.5), SpriteFactory::instance()->getText("Mp", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(14, 12.7, 0.5, 0.5), SpriteFactory::instance()->getText(":", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(14.3, 12.7, 0.5, 0.5), SpriteFactory::instance()->getText(std::to_string(hero->getMp()), { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(12.3, 13.3, 1.75, 0.5), SpriteFactory::instance()->getText("Gold", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(13.4, 13.3, 0.5, 0.5), SpriteFactory::instance()->getText(":", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(13.7, 13.3, 2, 0.5), SpriteFactory::instance()->getText(std::to_string(hero->getCoins()), { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(12.3, 13.9, 1.2, 0.5), SpriteFactory::instance()->getText("Keys", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(13.4, 13.9, 0.5, 0.5), SpriteFactory::instance()->getText(":", { 0.3f, 0.3f }));
				new RenderableObject(weaponmenu, RectF(13.7, 13.9, 0.5, 0.5), SpriteFactory::instance()->getText(std::to_string(hero->getKeys()), { 0.3f, 0.3f }));

				
				for (auto weapon : hero->getWeapons()) {
					if (weapon.second->getName() == hero->getWeapon()->getName()) {
						weaponmenu->addItem(1, i, weapon.second->getName() + " E", [weapon, hero]() {
							Pause_Menu* decision_menu = new Pause_Menu(1, 3, { 1,12 }, 7, 0, true);
							decision_menu->addItem(1, 1, "Equip", [weapon, hero]() {
								hero->equipWeapon(weapon.second);
								Game::instance()->popSceneLater();
								Game::instance()->popSceneLater();
								});
							decision_menu->addItem(1, 2, "Info", [weapon, hero]() {
								std::vector<std::string> dialogue = { "This weapon deals " + std::to_string(weapon.second->getDamage()) + "damage" };
								Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
								});
							decision_menu->addItem(1, 3, "Go back", []() {
								Game::instance()->popSceneLater();
								});
							Game::instance()->pushScene(decision_menu);
							});
						i++;
					}
					else {
						weaponmenu->addItem(1, i, weapon.second->getName(), [weapon, hero]() {
							Pause_Menu* decision_menu = new Pause_Menu(1, 3, { 1,12 }, 7, 0, true);
							decision_menu->addItem(1, 1, "Equip", [weapon, hero]() {
								hero->equipWeapon(weapon.second);
								Game::instance()->popSceneLater();
								Game::instance()->popSceneLater();
								});
							decision_menu->addItem(1, 2, "Info", [weapon, hero]() {
								std::vector<std::string> dialogue = { "This weapon deals " + std::to_string(weapon.second->getDamage())+" damage"};
								Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
								});
							decision_menu->addItem(1, 3, "Go back", []() {
								Game::instance()->popSceneLater();
								});
							Game::instance()->pushScene(decision_menu);
							});
						i++;
					}
				}
				weaponmenu->addItem(1, hero->getWeapons().size() + 1, "Back", [_hudBackground]() {
					Game::instance()->popSceneLater();
					});
				Game::instance()->pushScene(weaponmenu);
			}
			else {
				std::vector<std::string> dialogue = { "You have no weapons!" };
				Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
			}
		
		});




	Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
	Audio::instance()->pauseMusic();

	return menu;
}
Pause_Menu* Pause_Menu::deathMenu() {
	Pause_Menu* menu = new Pause_Menu(2,1,{ 2.5, 7.5 }, 6.0, 0, true);
	new RenderableObject(menu, RectF(0, 0, 20, 20), Color(0, 0, 0, 255));
	new RenderableObject(menu, RectF(3, 2, 9, 5), SpriteFactory::instance()->getText("Game Over"));
	menu->addItem(1, 1, "Retry", []() {
		Game::instance()->gameover();
		Game::instance()->popSceneLater();
		});
	menu->addItem(2, 1, "Quit", []() {
		Game::instance()->quit();
		});
	Audio::instance()->playMusic("20 Dragon Quest 1 - Thou Hast Died", 0);
	return menu;
}
void Pause_Menu::infoSpell(Spell* spell) {
	std::vector<std::string> dialogue = {};
	if (spell->getName() == "Life")
		dialogue = { "This spell costs " + std::to_string(spell->getCost()) + " mana points","It heals you 3 health points" };
	else if (spell->getName() == "Rage")
		dialogue = { "This spell costs " + std::to_string(spell->getCost()) + " mana points","It boosts your damage by 1","for the current battle" };
	else if(spell->getName()=="Light")
		dialogue = { "This spell costs " + std::to_string(spell->getCost()) + " mana points","It lights up dark places" };
	else if(spell->getName()=="Teleport")
		dialogue = { "This spell costs " + std::to_string(spell->getCost()) + " mana points","It brings you to the king's castle" };
	Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
}
void Pause_Menu::infoItem(Item* item) {
	std::vector<std::string> dialogue = {};
	if (item->getName() == "Health Potion")
		dialogue = { "It heals you 3 health points" };
	else if (item->getName() == "Mana Potion")
		dialogue = { "It heals you 3 mana points" };
	else if (item->getName() == "Torch")
		dialogue = { "It lights up dark places" };
	Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
}
Pause_Menu* Pause_Menu::pauseMenuSeller(Hero* hero, Seller* seller)
{
	if (seller->getOn()) {
		Pause_Menu* menu = new Pause_Menu(1, seller->_spells.size() + 1, { 1, 1 }, 10, 0, true);
		int i = 1;
		for (auto spell : seller->_spells) {

			menu->addItem(1, i, spell->getName()+" "+std::to_string(spell->getMoneyCost()) + " G", [spell, hero]()
				{

					Pause_Menu* decision_menu = new Pause_Menu(1, 3, { 1,12 }, 7, 0, true);
					decision_menu->addItem(1, 1, "Buy", [spell, hero]() {

						if (hero->checkSpell(spell)) {

							std::vector<std::string> dialogue = { "You already have this spell" };
							Game::instance()->popScene();
							Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
						}

						else if (hero->getCoins() >= spell->getMoneyCost()) {
							hero->addSpell(spell);
							hero->addCoins(-spell->getCost());
							Game::instance()->popSceneLater();
						}
						else {
							std::vector<std::string> dialogue = { "You don't have enough money" };
							Game::instance()->popScene();
							Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));

						}
						});
					decision_menu->addItem(1, 2, "Info", [decision_menu, spell]() {
						decision_menu->infoSpell(spell);
						});
					decision_menu->addItem(1, 3, "Don't buy", []() {
						Game::instance()->popSceneLater();
						});
					Game::instance()->pushScene(decision_menu);


				});

			i++;
		}
		menu->addItem(1, seller->_spells.size() + 1, "Back", []() {
			Game::instance()->popSceneLater();

			});
		Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
		Audio::instance()->pauseMusic();
		Audio::instance()->resumeMusic();

		return menu;

	}
	else {



		Pause_Menu* menu = new Pause_Menu(1, seller->_weapons.size() + seller->_items.size() + 1, { 1, 1 }, 10, 0, true);
		int i = 1;
		for (auto weapon : seller->_weapons) {

			menu->addItem(1, i, weapon->getName() + " " + std::to_string(weapon->getCost()) + " G", [weapon, hero]()
				{

					Pause_Menu* decision_menu = new Pause_Menu(1, 3, { 1,12 }, 7, 0, true);
					decision_menu->addItem(1, 1, "Buy", [weapon, hero]() {

						if (hero->checkWeapon(weapon)) {

							std::vector<std::string> dialogue = { "You already have this weapon" };
							Game::instance()->popScene();
							Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
						}

						else if (hero->getCoins() >= weapon->getCost()) {
							hero->addWeapon(weapon);
							hero->addCoins(-weapon->getCost());
							Game::instance()->popSceneLater();
						}

						else {
							std::vector<std::string> dialogue = { "You don't have enough money" };
							Game::instance()->popScene();
							Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));

						}
						});
					decision_menu->addItem(1, 2, "Info", [weapon, hero]() {
						std::vector<std::string> dialogue = { "This weapon deals " + std::to_string(weapon->getDamage()) + " damage" };
						Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
						});
					decision_menu->addItem(1, 3, "Don't buy", []() {
						Game::instance()->popSceneLater();
						});
					Game::instance()->pushScene(decision_menu);


				});

			i++;
		}
		int j = i;
		for (auto item : seller->_items) {

			menu->addItem(1, j, item->getName() + " " + std::to_string(item->getCost()) + " G", [item, hero]()
				{

					Pause_Menu* decision_menu1 = new Pause_Menu(1, 3, { 1,12 }, 7, 0, true);
					decision_menu1->addItem(1, 1, "Buy", [item, hero]() {

						if (hero->checkItem(item)>3) {

							std::vector<std::string> dialogue = { "You can't carry more","of this item" };
							Game::instance()->popScene();
							Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
						}

						else if (hero->getCoins() >= item->getCost()) {
							hero->addItem(item->getName());
							hero->addCoins(-item->getCost());
							Game::instance()->popSceneLater();
						}
						else {
							std::vector<std::string> dialogue = { "You don't have enough money" };
							Game::instance()->popScene();
							Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));

						}
						});
					decision_menu1->addItem(1, 2, "Info", [decision_menu1, item]() {
						decision_menu1->infoItem(item);
						});
					decision_menu1->addItem(1, 3, "Don't buy", []() {
						Game::instance()->popSceneLater();
						});
					Game::instance()->pushScene(decision_menu1);


				});

			j++;
		}
		menu->addItem(1, seller->_weapons.size() + seller->_items.size() + 1, "Back", []() {
			Game::instance()->popSceneLater();

			});
		Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
		Audio::instance()->pauseMusic();
		Audio::instance()->resumeMusic();

		return menu;

	}

}
Pause_Menu* Pause_Menu::victory_menu() {
	Pause_Menu* menu = new Pause_Menu(2, 1, { 2.5, 7.5 }, 6.0, 0, true);
	new RenderableObject(menu, RectF(0, 0, 20, 20), Color(0, 0, 0, 255));
	new RenderableObject(menu, RectF(3.5, 2, 9, 5), SpriteFactory::instance()->getText("Victory"));
	new RenderableObject(menu, RectF(11, 1.5, 1.5, 1.5),SpriteFactory::instance()->get("hero_princess_down"));
	menu->addItem(1, 1, "Reset", []() {
		Game::instance()->reset();
		Game::instance()->popSceneLater();
		});
	menu->addItem(2, 1, "Quit", []() {
		Game::instance()->quit();
		});
	Audio::instance()->playMusic("16 Dragon Quest 1 - Hero_s Fanfare", 0);
	return menu;
}