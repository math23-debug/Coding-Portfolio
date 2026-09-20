# Coding Portfolio

Learning software development through structured, progressively harder projects — from C++ fundamentals to SFML graphics programming to Python. This repo documents that progression and doubles as a portfolio.

## C++ Fundamentals

- **DiscountCalculator** — First project, refreshing basic C++ syntax. Simple function-based design.
- **Projectile** — Harder math (trig, `<cmath>`), still single-function based.
- **Password** — Introduced OOP (encapsulation) and STL (`std::string`).
- **Banking** — More complex OOP with class composition (a `Password` object inside a `Banking` class), input validation.
- **GradeTracker** — OOP combined with `std::vector` for dynamic data storage.
- **InventorySystem** — Custom `Item` class combined with `std::vector` for managing collections of objects.
- **TicTacToe** — 2D vectors (`std::vector<std::vector<char>>`) and win-condition logic.

## SFML Graphics Projects

- **BouncingBall** — First SFML project. Implements bouncing physics, a drag-to-launch slingshot mechanic, and velocity-based friction/deceleration.
- **CollectTheDot** — Sprite-based player movement, collision detection, a countdown timer, and score/high score tracking.
- **Pong** — Two-player paddle game with wall/paddle collision, scoring, and a win condition.
- **DodgeFallingObjects** — `std::vector` of falling obstacles with spawn timing and collision-based game over.
- **Snake** — Grid-based movement using a `std::deque`, self-collision detection, food spawning, and a checkerboard-rendered board.

## Python Projects

- **GradeTracker** — List-based grade tracking with input validation.
- **TextAnalyzer** — Word frequency, character frequency, sentence length analysis, and stop-word filtering using `re`, `Counter`, and list comprehensions.
- **ToDoList** — Persistent task storage using file I/O (`os.path.exists`, read/write).
- **QuoteScraper** — Web scraping with `requests` and `BeautifulSoup`, including pagination handling.
