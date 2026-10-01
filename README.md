# Watopoly

A fully object-oriented, terminal-based Monopoly variant set at the University of Waterloo — built from the ground up in modern C++20.

## Why You'll Love This Project

Watopoly isn't just a Monopoly clone with the names swapped out — it's a complete, from-scratch simulation engine built around a clean, extensible class hierarchy, C++20 modules, the Observer pattern, and genuine care for edge cases (bankruptcy, forced liquidation, doubles tracking, fair-bidding auctions, save/load, and more). Every square on the board, every card you draw, and every property you mortgage is backed by real polymorphic design rather than a pile of if-statements. If you want to see modern C++ applied to a real, playable, end-to-end game — this is it.

## The World of Waterloo, on a Board

Forget Boardwalk and Park Place — here you'll be trading in Waterloo's most iconic academic buildings, residences, and campus landmarks:

- **Academic Buildings** — AL, ML, ECH, PAS, HH, RCH, DWE, CPH, LHI, BMH, OPT, EV1, EV2, EV3, PHYS, B1, B2, EIT, ESC, C2, MC, DC, grouped into color/department sets (Arts, Eng, Health, Env, Sci, Math) exactly like Monopoly's property color groups — own the whole set to unlock improvements and supercharged rent.
- **Gyms** — PAC and CIF, rent scales with how many gyms a single player controls.
- **Residences** — MKV, UWP, V1, REV, rent scales with how many residences a single player controls.
- **DC Tims Line** — this game's "Jail." Get sent here, get stuck in line for up to 3 turns, and pay your way out, roll doubles, or burn a Tims Roll Up to escape.
- **SLC & Needles Hall** — Chance-style spaces that move you around the board, send you to the Tims Line, hand you OSAP money, or charge/credit you cash.
- **Money Changers** — Collect OSAP (Go), Tuition Fees, Coop Fees, and Goose Nesting (yes, the geese get you too).
- **Go To Tims** — the "Go to Jail" of Watopoly.

## A Full-Featured Game Engine

- 2-6 players, each represented by a themed piece (Goose, GRT Bus, Tim Hortons Doughnut, Professor, Student, Money, Laptop, Pink Tie).
- Buy properties on landing, or send them straight to a live, interactive auction if you pass.
- Two auction modes: a classic "last one standing" auction and a `-no-fair-bidding` rapid mode, selectable from the command line.
- Build and sell improvements on fully-owned academic building sets, up to 5 improvements per building, with rent scaling dramatically as you improve (e.g. AL's rent jumps from $2 unimproved all the way to $250 fully improved).
- Mortgage and unmortgage properties to stay solvent under pressure.
- Full trading system between players — cash-for-property, property-for-property, or straight cash-for-cash negotiations, with real accept/decline flow.
- Doubles tracking: roll doubles and go again, but roll three in a row and you're hauled off to the DC Tims Line.
- Tims Roll Ups: a randomized bonus card system that occasionally hands out a free "get out of the Tims Line" token instead of the usual charge/credit.
- Bankruptcy handling: when you can't pay up, liquidate assets property by property, trade your way out of trouble, or go bankrupt and have your entire estate auctioned off (or handed to your creditor).
- Save and load full game state to a file at any point and pick up exactly where you left off.
- A deterministic `-testing` mode with a scriptable `TestDice` implementation and extra debug commands (`addCash`, `charge`, `chargeForce`, `stop`) for repeatable, automatable playtesting.
- A beautifully rendered ASCII board, redrawn every turn, showing every player's position, every property's owner, and every improvement level at a glance.

## Engineered Like a Real Software Project

Under the hood, Watopoly is organized as a deep, purposeful class hierarchy using C++20 modules (`import`/`export`) instead of traditional headers:

```
Building (abstract base) - the root of every square on the board
├── Property (abstract) - anything ownable, mortgageable, tradable
│   ├── AcademicBuilding - department-set rent tiers & improvements
│   ├── Gym               - rent scales with gyms owned
│   └── Residence         - rent scales with residences owned
├── Chance (abstract) - "draw a card" squares
│   ├── SLC     - movement-based cards (forward/back/to Tims/to OSAP)
│   └── Needles - cash-based cards (charge or credit the player)
├── MoneyChange - flat fee/reward squares (OSAP, Tuition, Coop Fees)
├── GoToTims    - sends players directly to the Tims Line
└── TimsLine    - the jail mechanic itself, with its own turn counter
```

- **`Player` (interface)** implemented by `User` — decouples the board/engine logic from the concrete notion of a "player," making the system easy to extend or mock for testing.
- **`Trader` (interface)** implemented by `Board` — lets properties, chance cards, and users trigger trades/auctions without depending directly on the `Board` class, avoiding circular module dependencies.
- **`Dice` (interface)** implemented by `Dice` (real RNG) and `TestDice` (scripted, `IOManager`-driven rolls) — enables fully deterministic automated testing of game flow.
- **Observer pattern**: `Board::move()` triggers `notifyLand()`/`notifyNoLand()` on whatever `Building` occupies the landed-on square, so each square type fully owns its own behaviour (buy, charge rent, draw a card, go to the Tims Line, etc.) with zero special-casing in the game loop.
- **Non-Virtual Interface idiom** on `Property`: public mortgage/unmortgage logic lives in the base class, while behaviour that needs access to the concrete `User` type is pushed down to subclasses that can see it.
- **`IOManager`** centralizes all input/output and validation (including option-constrained prompts), keeping every other class free of direct `iostream` coupling and testable in isolation.
- **`FileManager`** serializes the entire board — every player's cash, position, Tims Roll Ups, Tims Line status, and every property's owner/mortgage/improvement state — into a human-readable save file, and reconstructs it exactly on load.

## Building & Running the Game

Watopoly is written in standard C++20 and compiles with g++'s experimental modules support (`-fmodules-ts`). The `Makefile` reads the full build order straight out of `order.txt` (interfaces first, then implementations, then `main.cc`) so modules are always compiled before anything that imports them.

```sh
make           # builds the "watopoly" executable
./watopoly     # play a normal game
```

Command-line flags:

| Flag               | Description                                                                                 |
| ------------------ | ------------------------------------------------------------------------------------------- |
| `-testing`         | enable scripted dice + extra debug commands (`addCash`, `charge`, `chargeForce`, `stop`)    |
| `-load <file>`     | resume a previously saved game from `<file>`                                                |
| `-no-fair-bidding` | use the classic single-winner auction style instead of the default fair multi-round auction |

In-game commands include `roll`, `next`, `trade <name> <give> <receive>`, `improve <property> <buy|sell>`, `mortgage <property>`, `unmortgage <property>`, `assets`, `all`, and `save <filename>`.

## Play Monopoly, the Waterloo Way

Whether you're here to relive campus life one Tims line at a time, study a clean real-world example of polymorphism, the Observer pattern, and modern C++ modules in action, or just want to bankrupt your friends over DC — Watopoly delivers the full board game experience in your terminal.

## Rules Reference

Watopoly follows the standard rules of Monopoly almost exactly, with Waterloo-flavoured renaming of spaces and cards. If you have a question, especially about mortgages and bankruptcy, these general Monopoly guides are a great place to start:

- https://www.wikihow.com/Play-Monopoly
- https://www.dicebreaker.com/games/monopoly/how-to/how-to-play-monopoly
