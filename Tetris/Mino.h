#pragma once

#include <vector>

using namespace std;

// 미노 모양
vector<vector<vector<vector<char>>>> mino{
	//I미노
	{{{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,1},
	  {0,0,0,0}},
	 {{0,0,1,0},
	  {0,0,1,0},
	  {0,0,1,0},
	  {0,0,1,0}},
	 {{0,0,0,0},
	  {1,1,1,1},
	  {0,0,0,0},
	  {0,0,0,0}},
	 {{0,1,0,0},
	  {0,1,0,0},
	  {0,1,0,0},
	  {0,1,0,0}}
	 },

	//O미노
  {{{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}}},

	//Z미노
	{{{0,0,0,0},
	  {1,1,0,0},
	  {0,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,0,1,0},
	  {0,1,1,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,0,0},
	  {0,1,1,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {1,1,0,0},
	  {1,0,0,0}}},


	//S미노
	{{{0,0,0,0},
	  {0,1,1,0},
	  {1,1,0,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {0,1,1,0},
	  {0,0,1,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {0,1,1,0},
	  {1,1,0,0}},
	 {{0,0,0,0},
	  {1,0,0,0},
	  {1,1,0,0},
	  {0,1,0,0}}},

	//J미노
	{{{0,0,0,0},
	  {1,0,0,0},
	  {1,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,1,0},
	  {0,1,0,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,0},
	  {0,0,1,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {0,1,0,0},
	  {1,1,0,0}}},

	//L미노
   {{{0,0,0,0},
	 {0,0,1,0},
	 {1,1,1,0},
	 {0,0,0,0}},
	{{0,0,0,0},
	 {0,1,0,0},
	 {0,1,0,0},
	 {0,1,1,0}},
	{{0,0,0,0},
	 {0,0,0,0},
	 {1,1,1,0},
	 {1,0,0,0}},
	{{0,0,0,0},
	 {1,1,0,0},
	 {0,1,0,0},
	 {0,1,0,0}}},

	//T미노
	{{{0,0,0,0},
	  {0,1,0,0},
	  {1,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {0,1,1,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {1,1,0,0},
	  {0,1,0,0}}}
};
