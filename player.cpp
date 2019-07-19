#include "player.h"

Player::Player() : Player::Player(1) {

}

Player::Player(int type) {
	minBet_ = 10;
	maxBet_ = 100;
	totalWins_ = 0;
	numberWinsRow_ = 0;
	lastBet_ = 10;
	bet_ = 10;
	currentAmount_ = 100;
	maximumAmount_ = currentAmount_;
	currentHandSum_ = 0;
	hasAce_ = false;
	doubled_ = false;
	lost_ = false;
	type_ = type;
}

Player::~Player() {}

void Player::addCard(int card) {

	if (card == ACE && (currentHandSum_ + 11 > 21)) {
		card = 1;
	}
	else if (card == ACE) {
		card = 11;
		hasAce_ = true;
	}

	if (hasAce_ && (currentHandSum_ + card > 21))
	{
		currentHandSum_ -= 10;
	}
	currentHandSum_ += card;
	if (currentHandSum_ > 21)
		lost_ = true;
}

bool Player::doubled() {
	return doubled_;
}

void Player::check(int dealer) {

	if ((currentHandSum_ > dealer || dealer > 21) && !lost_ ) {
		currentAmount_ += bet_;
		numberWinsRow_++;
		totalWins_++;
	}
	else if (currentHandSum_ < dealer || lost_) {
		currentAmount_ -= bet_;
		numberWinsRow_ = 0;
	}

	if (currentAmount_ > maximumAmount_)
		maximumAmount_ = currentAmount_;

	currentHandSum_ = 0;
	hasAce_ = false;
	doubled_ = false;
	lost_ = false;
}

int Player::play(int dealer) {
	if (doubled_ || lost_)
		return PASS;
	else if (currentHandSum_ >= 17)
		return PASS;
	else if (hasAce_ && currentHandSum_ < 18)
		return HIT;

	else if ((currentHandSum_ == 10 || currentHandSum_ == 11) && dealer < 7 && dealer > 1 && (currentAmount_ >= 2*bet_)) {
		doubled_ = true;
		bet_ *= 2;
		return HIT;
	}
	else if (currentHandSum_ <= 11)
		return HIT;
	else if (currentHandSum_ <= 13 && dealer >= 7)
		return HIT;
	else 
		return PASS;

}
int Player::bet() {
	if (currentAmount_ == 0)
		return 0;

	if (type_ == 1)
	{		// Adds on streaks, reset on loss
		if (numberWinsRow_ > 1)
		{
			if (lastBet_ > minBet_)
				lastBet_ -= 5;

			 bet_ = lastBet_;
		}
		else if (numberWinsRow_ == 1)
		{
			bet_ = lastBet_;
		}
		else
		{
			if (lastBet_ < maxBet_)
				lastBet_ += 5;

			bet_ = lastBet_;
		}
	}
	else if (type_ == 0)
		// Always bets the same
		bet_ = minBet_;

	return bet_;
}

bool Player::isDead() {
	if (currentAmount_ <= 0)
	{
		// std::cout << " Player type " << type_ << " Died with a maximum of " << maximumAmount_ << std::endl;
		return true;
	}

	return false;
}

int Player::getType() {
	return type_;
}
int Player::getMaximumAmount() {
	return maximumAmount_;
}
int Player::getTotalWins() {
	return totalWins_;
}

int Player::getHand() {
	return currentHandSum_;
}

int Player::getCurrentAmount() {
	return currentAmount_;
}

bool Player::lost() {
	return lost_;
}