#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::WIN] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WIN] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WIN] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WIN] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WIN] = false;

	matrix[Collider::Type::WIN][Collider::Type::WALL] = false;
	matrix[Collider::Type::WIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WIN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WIN][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WIN][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WIN][Collider::Type::WIN] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

UpdateResult ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// Remove all colliders scheduled for deletion
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
			{
				delete colliders[i];
				colliders[i] = nullptr;
			}
		}

		Collider* c1;
		Collider* c2;

		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			// skip empty colliders
			if (colliders[i] == nullptr)
				continue;

			c1 = colliders[i];

			// avoid checking collisions already checked
			for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
			{
				// skip empty colliders
				if (colliders[k] == nullptr)
					continue;

				c2 = colliders[k];

				if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
				{
					for (uint i = 0; i < MAX_LISTENERS; ++i)
						if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

					for (uint i = 0; i < MAX_LISTENERS; ++i)
						if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
				}
			}
		}
	
	}
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) debug = !debug;

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) GodModeF3 = !GodModeF3;

	//R dodge logic
	if (r != 0)
	{
		if (rpressed == false)
		{
			if (App->input->keys[SDL_SCANCODE_R] == KeyState::KEY_DOWN || App->input->pads->y == true)
			{
				rpressed = !rpressed;
				r--;
			}
		}
	}

	if (rpressed == false)
	{
		timer = 0;
		if (GodModeF3 == false)
		{
			godMode = false;
		}
		if (GodModeF3 == true)
		{
			godMode = true;
		}
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
		matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
		matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	}
	if (rpressed == true)
	{
		timer++;
		godMode = true;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = false;
		matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = false;
		if (timer / 450)
		{
			rpressed = !rpressed;
		}
	}
	

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleCollisions::PostUpdate()
{
	if (debug) DebugDraw();

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		if (godMode == false)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			case Collider::Type::WALL: // blue
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 0, 255, alpha });
				break;
			case Collider::Type::PLAYER: // green
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 255, 0, alpha });
				break;
			case Collider::Type::ENEMY: // red
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
				break;
			case Collider::Type::PLAYER_SHOT: // yellow
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 0, alpha });
				break;
			case Collider::Type::ENEMY_SHOT: // magenta
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 255, 255, alpha });
				break;
			case Collider::Type::WIN: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			}
		}
		else if (godMode == true)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			case Collider::Type::WALL: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			case Collider::Type::PLAYER: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			case Collider::Type::ENEMY: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			case Collider::Type::PLAYER_SHOT: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			case Collider::Type::ENEMY_SHOT: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			case Collider::Type::WIN: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
				break;
			}
		}
		//else if (GodModeF3 == true)
		//{
		//	switch (colliders[i]->type)
		//	{
		//	case Collider::Type::NONE: // white
		//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
		//		break;
		//	case Collider::Type::WALL: // white
		//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
		//		break;
		//	case Collider::Type::PLAYER: // white
		//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
		//		break;
		//	case Collider::Type::ENEMY: // white
		//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
		//		break;
		//	case Collider::Type::PLAYER_SHOT: // white
		//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
		//		break;
		//	case Collider::Type::ENEMY_SHOT: // white
		//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
		//		break;
		//	case Collider::Type::WIN: // white
		//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
		//		break;
		//	}
		//}
		
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}