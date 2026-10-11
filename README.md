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
- **nhlStats** — Pulls player stats from the NHL's public API (found by inspecting network requests in browser DevTools), with a name-normalized dictionary lookup and a player comparison feature.
- **NHLstatsGraph** — Loads NHL API data into a pandas DataFrame, with aggregation, filtering, top-10 sorting, and a goals vs. assists scatter plot using matplotlib.

## C++ In-Depth

Going under the hood of C++: manual memory management, smart pointers, templates, data structures built from scratch, and polymorphism with the STL.

- **MyVector (Evolution)** — A from-scratch dynamic array built in three stages:
  - **MyVector** — Raw-pointer implementation using `new[]`/`delete[]`, with size vs. capacity tracking, a `grow()` that reallocates and copies, and a deep-copy constructor and assignment operator (Rule of Three) with a self-assignment guard.
  - **MyVectorSafe** — Rewritten with `std::unique_ptr<int[]>` and `std::move`, removing the need for a manual destructor.
  - **MyVectorTemplate** — Generalized to `MyVector<T>` using templates.
- **LinkedList** — Node-based list with `push_front`, `pop_front`, `get`, `insert`, `remove`, and a destructor that walks and frees every node.
- **Stack** — LIFO container rebuilt from the linked list ideas.
- **Queue** — FIFO container using head and tail pointers for constant-time enqueue and dequeue.
- **EntitySystem** — Polymorphic `Entity` base class with `Player`, `Enemy`, and `Wall` derived types, stored in a `std::vector<std::unique_ptr<Entity>>`. Covers virtual functions, an abstract base class, virtual destructors, circle-hitbox collision with a virtual collision hook, and an `enum class` type ID. Uses STL algorithms with lambdas: `remove_if` (erase-remove), `find_if`, `sort`, and `any_of`.
