/* Enterprise C++ Handbook — Search Implementation
   Ctrl+K or clicking the search bar opens a modal.
   Results filter as you type. Click a result to navigate.
   Works on both dark (module0/1) and light (module2+) themes
   via CSS custom properties shared by both themes.
*/

(function () {
  // ─── Search index ──────────────────────────────────────────────
  var INDEX = [
    // Landing page
    { title: "Course Overview", sub: "All modules · 6 days", url: "index.html", tab: null,
      body: "enterprise cpp handbook foundations oop polymorphism robustness modern networking" },

    // Module 0
    { title: "Foundation Enhancer", sub: "Module 0 · Day 1", url: "module0.html", tab: null,
      body: "why cpp exists c to cpp migration procedural oop paradigm struct class malloc free new delete return codes exceptions toolchain setup g++ compiler" },
    { title: "Evolution of C to C++", sub: "Module 0 · Topic 01", url: "module0.html#t1", tab: "t1",
      body: "c language history bjarne stroustrup object oriented classes structs memory management why cpp replaced c procedural programming" },
    { title: "Procedural vs OOP", sub: "Module 0 · Topic 02", url: "module0.html#t2", tab: "t2",
      body: "procedural paradigm oop paradigm data behaviour encapsulation object state method procedure function" },
    { title: "Key C to C++ Differences", sub: "Module 0 · Topic 03", url: "module0.html#t3", tab: "t3",
      body: "struct class malloc free new delete return codes exceptions references namespaces std cout cin endl" },

    // Module 1
    { title: "C++ Basics", sub: "Module 1 · Day 1", url: "module1.html", tab: null,
      body: "classes objects access specifiers constructors destructors static members friend functions bank account case study" },
    { title: "Classes & Objects", sub: "Module 1 · Topic 01", url: "module1.html#t1", tab: "t1",
      body: "class keyword object instance stack allocation heap allocation new delete member function data member BankAccount" },
    { title: "Access Specifiers", sub: "Module 1 · Topic 02", url: "module1.html#t2", tab: "t2",
      body: "public private protected encapsulation data hiding getter setter balance validation access control" },
    { title: "Constructors & Destructors", sub: "Module 1 · Topic 03", url: "module1.html#t3", tab: "t3",
      body: "default constructor parameterized copy constructor destructor initializer list uninitialised state resource cleanup" },
    { title: "Static Members", sub: "Module 1 · Topic 04", url: "module1.html#t4", tab: "t4",
      body: "static data member static method class-level variable shared across instances total accounts bank" },
    { title: "Friend Functions", sub: "Module 1 · Topic 05", url: "module1.html#t5", tab: "t5",
      body: "friend function friend class access private members audit comparison transfer between accounts" },

    // Module 2
    { title: "Inheritance & Polymorphism", sub: "Module 2 · Day 2", url: "module2.html", tab: null,
      body: "inheritance virtual functions abstract classes destructors vtable shape hierarchy runtime polymorphism" },
    { title: "Inheritance", sub: "Module 2 · Topic 01", url: "module2.html#t1", tab: "t1",
      body: "base class derived class public inheritance colon syntax is-a relationship code reuse Shape Circle Rectangle constructor chaining Vehicle Car" },
    { title: "Virtual Functions", sub: "Module 2 · Topic 02", url: "module2.html#t2", tab: "t2",
      body: "virtual keyword override dynamic dispatch runtime binding vtable vptr static binding draw shape polymorphism C# comparison" },
    { title: "Abstract Classes", sub: "Module 2 · Topic 03", url: "module2.html#t3", tab: "t3",
      body: "pure virtual function abstract class interface contract cannot instantiate area name shape circle rectangle compile-time enforcement" },
    { title: "Virtual Destructors & vtables", sub: "Module 2 · Topic 04", url: "module2.html#t4", tab: "t4",
      body: "virtual destructor memory leak resource cleanup vtable vptr pointer delete base derived ManagedBuffer Resource" },

    // Module 3
    { title: "Compile-time Polymorphism", sub: "Module 3 · Day 2", url: "module3.html", tab: null,
      body: "function overloading operator overloading complex numbers point comparison compile-time dispatch" },
    { title: "Function Overloading", sub: "Module 3 · Topic 01", url: "module3.html#t1", tab: "t1",
      body: "overload resolution same name different parameters types int double string add overloading compile-time selection" },
    { title: "Operator Overloading", sub: "Module 3 · Topic 02", url: "module3.html#t2", tab: "t2",
      body: "operator+ operator== operator!= operator< operator<< member function free function vector2d value type" },
    { title: "Complex Numbers", sub: "Module 3 · Topic 03", url: "module3.html#t3", tab: "t3",
      body: "complex number real imaginary addition multiplication operator overloading value type component-wise arithmetic" },
    { title: "Point Comparison", sub: "Module 3 · Topic 04", url: "module3.html#t4", tab: "t4",
      body: "point equality floating point tolerance epsilon operator== operator!= operator< checkpoint player game coordinate comparison" },

    // Module 4
    { title: "Exception Handling & Robustness", sub: "Module 4 · Day 3", url: "module4.html", tab: null,
      body: "try catch throw exception RAII runtime_error custom exception robust payment processor error handling" },
    { title: "try/catch basics", sub: "Module 4 · Topic 01", url: "module4.html#t1", tab: "t1",
      body: "try block throw statement catch clause stack unwinding std::runtime_error return codes error code trap divide by zero program survives" },
    { title: "Catch by type", sub: "Module 4 · Topic 02", url: "module4.html#t2", tab: "t2",
      body: "multiple catch clauses std::exception hierarchy std::invalid_argument std::out_of_range catch order what() typed exceptions context" },
    { title: "Custom Exceptions", sub: "Module 4 · Topic 03", url: "module4.html#t3", tab: "t3",
      body: "custom exception class inherit std::exception what() noexcept override domain context InsufficientFundsError typed members account balance" },
    { title: "RAII", sub: "Module 4 · Topic 04", url: "module4.html#t4", tab: "t4",
      body: "RAII resource acquisition initialization constructor destructor file handle ifstream ofstream lock_guard unique_ptr exception safe FileReader always closes" },

    // Module 5
    { title: "Templates & Generics", sub: "Module 5 · Day 3", url: "module5.html", tab: null,
      body: "function template class template STL standard template library generic programming type parameter typename" },
    { title: "Why Templates", sub: "Module 5 · Topic 01", url: "module5.html#t1", tab: "t1",
      body: "code duplication problem type parameter compile-time code generation zero runtime overhead template instantiation maxOf typename vs class header file" },
    { title: "Function Templates", sub: "Module 5 · Topic 02", url: "module5.html#t2", tab: "t2",
      body: "template<typename T> type deduction const T& explicit template argument swap clamp non-type parameter void* type safety" },
    { title: "Class Templates", sub: "Module 5 · Topic 03", url: "module5.html#t3", tab: "t3",
      body: "class template Stack<T> member function outside definition distinct instantiation multiple type parameters vector int string" },
    { title: "STL as Templates", sub: "Module 5 · Topic 04", url: "module5.html#t4", tab: "t4",
      body: "std::vector std::map std::unordered_map std::optional std::pair std::unique_ptr std::sort std::find_if standard template library container algorithm" },

    // Module 6
    { title: "STL & Containers", sub: "Module 6 · Day 4", url: "module6.html", tab: null,
      body: "standard template library vector list deque map set unordered_map sort find_if count_if accumulate iterators student records analyzer" },
    { title: "Sequence Containers", sub: "Module 6 · Topic 01", url: "module6.html#t1", tab: "t1",
      body: "std::vector std::list std::deque contiguous memory linked list double ended queue push_back insert erase" },
    { title: "Associative Containers", sub: "Module 6 · Topic 02", url: "module6.html#t2", tab: "t2",
      body: "std::map std::set std::unordered_map key value pairs sorted order hash table lookup insert find" },
    { title: "Algorithms", sub: "Module 6 · Topic 03", url: "module6.html#t3", tab: "t3",
      body: "std::sort std::find_if std::count_if std::transform std::accumulate lambda predicate comparator range" },
    { title: "Iterators", sub: "Module 6 · Topic 04", url: "module6.html#t4", tab: "t4",
      body: "iterator categories begin end back_inserter ostream_iterator traversal container-agnostic" },

    // Module 7
    { title: "Advanced C++ Features", sub: "Module 7 · Day 4", url: "module7.html", tab: null,
      body: "lambdas smart pointers file io multithreading unique_ptr shared_ptr weak_ptr thread mutex async future concurrent sensor log aggregator" },
    { title: "Lambdas", sub: "Module 7 · Topic 01", url: "module7.html#t1", tab: "t1",
      body: "lambda expression capture by value capture by reference std::function anonymous function inline callback" },
    { title: "Smart Pointers", sub: "Module 7 · Topic 02", url: "module7.html#t2", tab: "t2",
      body: "unique_ptr shared_ptr weak_ptr make_unique make_shared reference counting ownership memory leak double delete use after free" },
    { title: "File I/O", sub: "Module 7 · Topic 03", url: "module7.html#t3", tab: "t3",
      body: "ofstream ifstream fstream RAII file handling getline ios::app append mode" },
    { title: "Multithreading", sub: "Module 7 · Topic 04", url: "module7.html#t4", tab: "t4",
      body: "std::thread std::mutex lock_guard std::async std::future data race join detach concurrency" },

    // Module 8
    { title: "Systems Programming & Advanced C++ Internals", sub: "Module 8 · Day 5", url: "module8.html", tab: null,
      body: "networking sockets move semantics pipes file descriptors linking system info rtti typeid dynamic_cast fleet diagnostics relay agent" },
    { title: "Networking", sub: "Module 8 · Topic 01", url: "module8.html#t1", tab: "t1",
      body: "tcp udp sockets winsock bind listen accept connect send recv client server chat" },
    { title: "Move Semantics", sub: "Module 8 · Topic 02", url: "module8.html#t2", tab: "t2",
      body: "rvalue reference lvalue reference std::move move constructor moved-from state avoid copies" },
    { title: "Pipes & File Descriptors", sub: "Module 8 · Topic 03", url: "module8.html#t3", tab: "t3",
      body: "CreatePipe CreateProcess anonymous pipe inter-process communication ipc file descriptor handle parent child process" },
    { title: "Linking: Static vs Dynamic", sub: "Module 8 · Topic 04", url: "module8.html#t4", tab: "t4",
      body: "static library dynamic library dll shared object ar linker object file translation unit header" },
    { title: "Reading System Info", sub: "Module 8 · Topic 05", url: "module8.html#t5", tab: "t5",
      body: "SYSTEM_INFO GetSystemInfo MEMORYSTATUSEX GlobalMemoryStatusEx hardware_concurrency cpu cores memory" },
    { title: "Additional Topics: RTTI", sub: "Module 8 · Topic 06", url: "module8.html#t6", tab: "t6",
      body: "typeid dynamic_cast RTTI run-time type information polymorphic type identification bad_cast" },

    // Capstone exercises
    { title: "Capstone: RR Skillverse Course Tracker", sub: "Practice lab", url: "exercise.html", tab: null,
      body: "capstone exercise course tracker classes inheritance virtual dispatch operator overloading complete program" },
    { title: "Capstone: Smart Office Access System", sub: "Practice lab", url: "capstone-work1.html", tab: null,
      body: "smart office badge access employee contractor visitor polymorphism capstone exercise" },
    { title: "Capstone-Work2: Nimbus Logistics Challenge", sub: "Practice lab", url: "capstone-work2.html", tab: null,
      body: "nimbus logistics challenge mode templates stl exceptions inheritance overloading repository generic order fulfillment unfinished features todo capstone" },
    { title: "Capstone-Work3: Nimbus Fleet Command", sub: "Practice lab", url: "capstone-work3.html", tab: null,
      body: "nimbus fleet command diagnostics agent networking move semantics pipes linking system info rtti unfinished features todo capstone static library" },

    // C++ in the Wild: real-world analogues
    { title: "C++ in the Wild", sub: "Real-world analogues · Module 0-10", url: "cpp-in-the-wild.html", tab: null,
      body: "real world examples analogues where concepts are used game development banking mobile qt qml hardware sensor domain applications best practices never forget checklist" },
    { title: "Module 0 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t0", tab: "t0",
      body: "pointers pass by value pass by reference procedural vs oop c vs cpp real world game engines embedded firmware" },
    { title: "Module 1 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t1", tab: "t1",
      body: "classes objects access specifiers constructors destructors static members friend functions real world banking e-commerce" },
    { title: "Module 2 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t2", tab: "t2",
      body: "inheritance virtual functions abstract classes vtables real world qt widgets game engines payment gateways plugins" },
    { title: "Module 3 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t3", tab: "t3",
      body: "function overloading operator overloading real world math graphics libraries cad scientific computing" },
    { title: "Module 4 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t4", tab: "t4",
      body: "try catch custom exceptions raii real world point of sale airline booking robotics" },
    { title: "Module 5 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t5", tab: "t5",
      body: "templates generics real world trading systems search engines game math utilities" },
    { title: "Module 6 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t6", tab: "t6",
      body: "sequence containers associative containers algorithms iterators real world dns cache log analysis" },
    { title: "Module 7 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t7", tab: "t7",
      body: "lambdas smart pointers file io multithreading real world asset management ride hailing video editors" },
    { title: "Module 8 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t8", tab: "t8",
      body: "networking move semantics pipes linking system info rtti real world multiplayer games qt qml sensors" },
    { title: "Module 9 real-world analogues", sub: "C++ in the Wild", url: "cpp-in-the-wild.html#t9", tab: "t9",
      body: "qt widgets signals slots qml qt quick qt networking real world vlc wireshark autodesk maya automotive dashboards medical devices industrial touchscreens iot gateways" },
    { title: "Module 10 real-world analogues", sub: "C++ in the Wild · Hall of Fame", url: "cpp-in-the-wild.html#t10", tab: "t10",
      body: "real world c++ hall of fame unreal engine id tech chromium v8 mysql mongodb sql server photoshop maya high frequency trading ros robot operating system nasa jpl f prime ingenuity mars helicopter radar avionics famous software" },
    { title: "Best Practices — Never Forget", sub: "C++ in the Wild · Quick reminders", url: "cpp-in-the-wild.html#t11", tab: "t11",
      body: "best practices never forget new delete unique_ptr shared_ptr weak_ptr memory leak double free wsastartup wsacleanup socket closesocket createpipe createprocess closehandle thread join detach mutex lock_guard raii placement new destructor acquire release checklist reminders" },

    // Practice MCQ Tests: interactive pre-test / module-wise tests / post-test
    { title: "Practice MCQ Tests", sub: "Interactive · 7 tests, instant feedback", url: "practice-tests.html", tab: null,
      body: "practice mcq tests quiz pre-test post-test module wise test interactive instant feedback right wrong correct answer explanation diagnostic holistic review" },
    { title: "Pre-Test", sub: "Practice MCQ Tests · Diagnostic, all 6 days", url: "practice-tests.html#pretest", tab: null,
      body: "pretest diagnostic quiz all modules day 1 to day 6" },
    { title: "Module-wise Test 1", sub: "Practice MCQ Tests · Module 0 + Module 1", url: "practice-tests.html#mwt1", tab: null,
      body: "module wise test 1 quiz foundation c++ basics day 1" },
    { title: "Module-wise Test 2", sub: "Practice MCQ Tests · Module 2 + Module 3", url: "practice-tests.html#mwt2", tab: null,
      body: "module wise test 2 quiz inheritance polymorphism compile-time day 2" },
    { title: "Module-wise Test 3", sub: "Practice MCQ Tests · Module 4 + Module 5", url: "practice-tests.html#mwt3", tab: null,
      body: "module wise test 3 quiz exception handling templates generics day 3" },
    { title: "Module-wise Test 4", sub: "Practice MCQ Tests · Module 6 + Module 7", url: "practice-tests.html#mwt4", tab: null,
      body: "module wise test 4 quiz stl containers advanced features smart pointers threading day 4" },
    { title: "Module-wise Test 5", sub: "Practice MCQ Tests · Module 8 + Module 9", url: "practice-tests.html#mwt5", tab: null,
      body: "module wise test 5 quiz networking qt qml day 5" },
    { title: "Post-Test", sub: "Practice MCQ Tests · Holistic, Module 10 + all 6 days", url: "practice-tests.html#posttest", tab: null,
      body: "post-test quiz holistic final review module 10 wrap-up day 6" },

    // Explore More: student questions and follow-up explanations
    { title: "Explore More", sub: "Student questions · 2 entries", url: "explore-more.html", tab: null,
      body: "student questions curiosity follow-up explanations virtual keyword calling conventions cricket demo" },
    { title: "Why use the virtual keyword?", sub: "Explore More · Polymorphism", url: "explore-more.html#virtual-keyword", tab: null,
      body: "virtual keyword real use runtime polymorphism dispatch vtable vptr base pointer reference child object parent type override virtual destructor" },
    { title: "Calling conventions cricket demo", sub: "Explore More · Calling conventions", url: "explore-more.html#cricket-calling-conventions", tab: null,
      body: "3_calling_conventionscricket demo theory code snippets calling conventions ABI stack registers cdecl stdcall thiscall fastcall" },
  ];

  // ─── Score a result against a query ─────────────────────────────
  function score(entry, query) {
    var q = query.toLowerCase();
    var title = entry.title.toLowerCase();
    var sub   = entry.sub.toLowerCase();
    var body  = entry.body.toLowerCase();
    if (title.includes(q)) return 3;
    if (sub.includes(q))   return 2;
    // token search in body
    var tokens = q.split(/\s+/).filter(Boolean);
    var matched = tokens.filter(function(t) { return body.includes(t); });
    if (matched.length === tokens.length) return 1;
    if (matched.length > 0) return 0.5;
    return 0;
  }

  // ─── Resolve a search-index url to the right relative path ──────
  // This file's own url values (e.g. "module0.html", "index.html") are
  // all written as if every page lived in one flat folder together. In
  // reality, index.html sits at the repo root while every other page
  // lives one level down in site/ (where this script itself lives) — so
  // "index.html" needs "../" prepended when we're already inside site/,
  // and every OTHER url needs "site/" prepended when we're being viewed
  // from the root index.html instead.
  function resolveUrl(url) {
    var inSite = /(^|\/)site\//.test(location.pathname);
    var isIndex = url === 'index.html' || url.indexOf('index.html#') === 0;
    if (isIndex) return inSite ? '../' + url : url;
    return inSite ? url : 'site/' + url;
  }

  // ─── Navigate to a search result ────────────────────────────────
  function navigate(entry) {
    if (entry.tab) {
      // Navigate to the page, then activate the tab via hash
      var current = location.pathname.split('/').pop();
      var target  = entry.url.split('#')[0];
      if (current === target || (current === '' && target === 'index.html')) {
        // Same page — just activate the tab
        var hash = entry.url.split('#')[1];
        if (hash) {
          var btn = document.querySelector('[data-tab="' + hash + '"]');
          if (btn) btn.click();
          location.hash = hash;
        }
      } else {
        location.href = resolveUrl(entry.url);
      }
    } else {
      location.href = resolveUrl(entry.url);
    }
    closeModal();
  }

  // ─── Render results ──────────────────────────────────────────────
  function renderResults(query, list, container) {
    container.innerHTML = '';
    if (!query || query.length < 2) {
      container.innerHTML = '<div class="sr-empty">Type at least 2 characters to search…</div>';
      return;
    }
    var scored = INDEX.map(function(e) {
      return { entry: e, s: score(e, query) };
    }).filter(function(x) { return x.s > 0; })
      .sort(function(a, b) { return b.s - a.s; })
      .slice(0, 12);

    if (scored.length === 0) {
      container.innerHTML = '<div class="sr-empty">No results for "<strong>' + escHtml(query) + '</strong>"</div>';
      return;
    }
    scored.forEach(function(x, i) {
      var e = x.entry;
      var el = document.createElement('button');
      el.className = 'sr-item' + (i === 0 ? ' sr-item--active' : '');
      el.type = 'button';
      el.innerHTML =
        '<span class="sr-title">' + escHtml(e.title) + '</span>' +
        '<span class="sr-sub">' + escHtml(e.sub) + '</span>';
      el.addEventListener('click', function() { navigate(e); });
      list.appendChild(el);
    });
  }

  function escHtml(s) {
    return s.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
  }

  // ─── Keyboard navigation within results ─────────────────────────
  function moveFocus(list, dir) {
    var items = list.querySelectorAll('.sr-item');
    if (!items.length) return;
    var active = list.querySelector('.sr-item--active');
    var idx = -1;
    items.forEach(function(el, i) { if (el === active) idx = i; });
    if (active) active.classList.remove('sr-item--active');
    idx = (idx + dir + items.length) % items.length;
    items[idx].classList.add('sr-item--active');
    items[idx].scrollIntoView({ block: 'nearest' });
  }

  // ─── Modal open / close ──────────────────────────────────────────
  var overlay, modal, input, list;

  function openModal() {
    if (overlay) { overlay.style.display = 'flex'; input.focus(); input.select(); return; }
    injectStyles();
    overlay = document.createElement('div');
    overlay.className = 'sr-overlay';
    overlay.setAttribute('role', 'dialog');
    overlay.setAttribute('aria-modal', 'true');
    overlay.setAttribute('aria-label', 'Search the handbook');

    modal = document.createElement('div');
    modal.className = 'sr-modal';

    var searchRow = document.createElement('div');
    searchRow.className = 'sr-searchrow';

    var icon = document.createElement('span');
    icon.className = 'sr-icon';
    icon.textContent = '⌕';

    input = document.createElement('input');
    input.type = 'search';
    input.className = 'sr-input';
    input.placeholder = 'Search modules, topics, concepts…';
    input.autocomplete = 'off';
    input.spellcheck = false;

    var closeBtn = document.createElement('button');
    closeBtn.className = 'sr-close';
    closeBtn.type = 'button';
    closeBtn.setAttribute('aria-label', 'Close search');
    closeBtn.textContent = '✕';
    closeBtn.addEventListener('click', closeModal);

    searchRow.appendChild(icon);
    searchRow.appendChild(input);
    searchRow.appendChild(closeBtn);

    list = document.createElement('div');
    list.className = 'sr-list';
    list.innerHTML = '<div class="sr-empty">Type at least 2 characters to search…</div>';

    var footer = document.createElement('div');
    footer.className = 'sr-footer';
    footer.innerHTML = '<span>↑↓ navigate</span><span>↵ open</span><span>Esc close</span>';

    modal.appendChild(searchRow);
    modal.appendChild(list);
    modal.appendChild(footer);
    overlay.appendChild(modal);
    document.body.appendChild(overlay);

    input.addEventListener('input', function() {
      renderResults(input.value.trim(), list, list);
    });

    input.addEventListener('keydown', function(e) {
      if (e.key === 'ArrowDown')  { e.preventDefault(); moveFocus(list, 1); }
      if (e.key === 'ArrowUp')    { e.preventDefault(); moveFocus(list, -1); }
      if (e.key === 'Escape')     { closeModal(); }
      if (e.key === 'Enter') {
        var active = list.querySelector('.sr-item--active');
        if (active) active.click();
      }
    });

    overlay.addEventListener('click', function(e) {
      if (e.target === overlay) closeModal();
    });

    requestAnimationFrame(function() { input.focus(); });
  }

  function closeModal() {
    if (overlay) overlay.style.display = 'none';
  }

  // ─── Wire up the existing search bar on the page ─────────────────
  function wireSearchBar() {
    var bars = document.querySelectorAll('.search-input');
    bars.forEach(function(bar) {
      bar.addEventListener('focus', function(e) {
        e.preventDefault();
        bar.blur();
        openModal();
      });
      bar.parentElement.addEventListener('click', function(e) {
        e.preventDefault();
        openModal();
      });
    });
  }

  // ─── Global keyboard shortcut Ctrl+K / Cmd+K ─────────────────────
  document.addEventListener('keydown', function(e) {
    if ((e.ctrlKey || e.metaKey) && e.key === 'k') {
      e.preventDefault();
      openModal();
    }
    if (e.key === 'Escape' && overlay && overlay.style.display !== 'none') {
      closeModal();
    }
  });

  // ─── Inject CSS ───────────────────────────────────────────────────
  function injectStyles() {
    if (document.getElementById('sr-styles')) return;
    var s = document.createElement('style');
    s.id = 'sr-styles';
    // Uses CSS custom properties that exist on both dark and light theme pages.
    // Falls back to reasonable values if a variable isn't set.
    s.textContent = [
      '.sr-overlay{',
        'position:fixed;inset:0;z-index:9999;',
        'display:flex;align-items:flex-start;justify-content:center;',
        'padding-top:80px;',
        'background:rgba(0,0,0,0.55);',
        'backdrop-filter:blur(3px);',
      '}',
      '.sr-modal{',
        'width:min(680px,calc(100vw - 32px));',
        'background:var(--surface,#fff);',
        'border:1px solid var(--border,#e5e7eb);',
        'border-radius:14px;',
        'box-shadow:0 24px 64px rgba(0,0,0,0.35);',
        'overflow:hidden;',
        'display:flex;flex-direction:column;',
        'max-height:calc(100vh - 140px);',
      '}',
      '.sr-searchrow{',
        'display:flex;align-items:center;gap:12px;',
        'padding:16px 18px;',
        'border-bottom:1px solid var(--border,#e5e7eb);',
        'flex-shrink:0;',
      '}',
      '.sr-icon{font-size:20px;color:var(--text-faint,#94a3b8);flex-shrink:0;}',
      '.sr-input{',
        'flex:1;border:none;outline:none;',
        'background:transparent;',
        'font-size:16px;color:var(--text,#1e293b);',
        'font-family:inherit;',
      '}',
      '.sr-input::placeholder{color:var(--text-faint,#94a3b8);}',
      '.sr-close{',
        'background:none;border:none;cursor:pointer;',
        'color:var(--text-faint,#94a3b8);font-size:16px;padding:4px 6px;',
        'border-radius:6px;flex-shrink:0;',
      '}',
      '.sr-close:hover{color:var(--text,#1e293b);background:var(--surface-2,#f1f5f9);}',
      '.sr-list{overflow-y:auto;flex:1;padding:8px;}',
      '.sr-item{',
        'width:100%;text-align:left;',
        'display:flex;flex-direction:column;gap:2px;',
        'padding:10px 14px;border-radius:8px;border:none;',
        'cursor:pointer;background:transparent;',
        'color:var(--text,#1e293b);',
      '}',
      '.sr-item:hover,.sr-item--active{',
        'background:var(--surface-2,#f1f5f9);',
      '}',
      '.sr-title{font-size:14px;font-weight:600;color:var(--text,#1e293b);}',
      '.sr-sub{font-size:12px;color:var(--text-faint,#94a3b8);font-family:monospace;}',
      '.sr-empty{',
        'padding:24px 14px;text-align:center;',
        'color:var(--text-faint,#94a3b8);font-size:14px;',
      '}',
      '.sr-footer{',
        'display:flex;gap:20px;justify-content:center;',
        'padding:10px 18px;',
        'border-top:1px solid var(--border,#e5e7eb);',
        'font-size:12px;color:var(--text-faint,#94a3b8);',
        'flex-shrink:0;',
      '}',
    ].join('');
    document.head.appendChild(s);
  }

  // ─── Init ─────────────────────────────────────────────────────────
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', wireSearchBar);
  } else {
    wireSearchBar();
  }
})();
