#pragma once

#include "Mino.h"

bool minoRotation(int nowMino, int degree, int pos_x, int pos_y, vector<vector<string>>& field)
{
	switch (nowMino)
	{
	case 0:
		switch (degree)
		{
		case 0:
			if (field[pos_y + 3][pos_x + 2] == "  " && field[pos_y + 1][pos_x + 2] == "  " && field[pos_y][pos_x + 2] == "  ")
				return true;
			break;
		case 1:
			if (pos_x > 0)
				if (field[pos_y + 1][pos_x] == "  " && field[pos_y + 1][pos_x + 1] == "  " && field[pos_y + 1][pos_x + 3] == "  ")
					return true;
			break;
		case 2:
			if (pos_y > 0)
				if (field[pos_y + 3][pos_x + 1] == "  " && field[pos_y + 2][pos_x + 1] == "  " && field[pos_y][pos_x + 1] == "  ")
					return true;
			break;
		case 3:
			if (pos_x < 12)
				if (field[pos_y + 2][pos_x] == "  " && field[pos_y + 2][pos_x + 2] == "  " && field[pos_y + 2][pos_x + 3] == "  ")
					return true;
			break;
		}
		break;
	case 1:
		return true;
		break;
		
	case 2:
		switch (degree)
		{
		case 0:
			if (field[pos_y + 3][pos_x + 1] == "  " && field[pos_y + 1][pos_x + 2] == "  ")
				return true;
			break;
		case 1:
			if (field[pos_y + 2][pos_x] == "  " && field[pos_y + 3][pos_x + 2] == "  ")
				return true;
			break;
		case 2:
			if (field[pos_y + 3][pos_x] == "  " && field[pos_y + 1][pos_x + 1] == "  ")
				return true;
			break;
		case 3:
			if (field[pos_y + 1][pos_x] == "  " && field[pos_y + 2][pos_x + 2] == "  ")
				return true;
			break;
		}
		break;
	case 3:
		switch (degree)
		{
		case 0:
			if (field[pos_y + 3][pos_x + 2] == "  " && field[pos_y + 2][pos_x + 2] == "  ")
				return true;
			break;
		case 1:
			if (field[pos_y + 3][pos_x] == "  " && field[pos_y + 3][pos_x + 1] == "  ")
				return true;
			break;
		case 2:
			if (field[pos_y + 2][pos_x] == "  " && field[pos_y + 1][pos_x] == "  ")
				return true;
			break;
		case 3:
			if (field[pos_y + 1][pos_x + 1] == "  " && field[pos_y + 1][pos_x + 2] == "  ")
				return true;
			break;
		}
		break;
	case 4:
		switch (degree)
		{
		case 0:
			if (field[pos_y + 1][pos_x + 2] == "  " && field[pos_y + 1][pos_x + 1] == "  " && field[pos_y + 3][pos_x + 1] == "  ")
				return true;
			break;
		case 1:
			if (field[pos_y + 2][pos_x] == "  " && field[pos_y + 2][pos_x + 2] == "  " && field[pos_y + 3][pos_x + 2] == "  ")
				return true;
			break;
		case 2:
			if (field[pos_y + 3][pos_x + 1] == "  " && field[pos_y + 1][pos_x + 1] == "  " && field[pos_y + 3][pos_x] == "  ")
				return true;
			break;
		case 3:
			if (field[pos_y + 2][pos_x] == "  " && field[pos_y + 1][pos_x] == "  " && field[pos_y + 2][pos_x + 2] == "  ")
				return true;
			break;
		}
		break;
	case 5:
		switch (degree)
		{
		case 0:
			if (field[pos_y + 1][pos_x + 1] == "  " && field[pos_y + 3][pos_x + 1] == "  " && field[pos_y + 3][pos_x + 2] == "  ")
				return true;
			break;
		case 1:
			if (field[pos_y + 2][pos_x] == "  " && field[pos_y + 2][pos_x + 2] == "  " && field[pos_y + 3][pos_x] == "  ")
				return true;
			break;
		case 2:
			if (field[pos_y + 3][pos_x + 1] == "  " && field[pos_y + 1][pos_x + 1] == "  " && field[pos_y + 1][pos_x] == "  ")
				return true;
			break;
		case 3:
			if (field[pos_y + 2][pos_x] == "  " && field[pos_y + 2][pos_x + 2] == "  " && field[pos_y + 1][pos_x + 2] == "  ")
				return true;
			break;
		}
		break;
	case 6:
		switch (degree)
		{
		case 0:
			if (field[pos_y + 3][pos_x + 1] == "  ")
				return true;
			break;
		case 1:
			if (field[pos_y + 2][pos_x] == "  ")
				return true;
			break;
		case 2:
			if (field[pos_y + 1][pos_x + 1] == "  ")
				return true;
			break;
		case 3:
			if (field[pos_y + 2][pos_x + 2] == "  ")
				return true;
			break;
		}
		break;
	}
	return false;
}