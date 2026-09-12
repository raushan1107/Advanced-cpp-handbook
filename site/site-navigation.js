(function () {
  const inSiteFolder = /[\\/]site[\\/]/.test(window.location.pathname);
  const prefix = inSiteFolder ? '' : 'site/';
  const home = prefix + '../index.html';
  const link = (href, label, icon) => '<a href="' + prefix + href + '">' + (icon ? icon + ' ' : '') + label + '</a>';
  const external = (href, label, icon) => '<a href="' + href + '" target="_blank" rel="noopener">' + (icon ? icon + ' ' : '') + label + ' <span aria-hidden="true">↗</span></a>';

  const modules = [
    ['Day 1', 'Foundations', [['module0.html', 'Foundation Enhancer'], ['module1.html', 'C++ Basics']]],
    ['Day 2', 'Polymorphism', [['module2.html', 'Inheritance & Polymorphism'], ['module3.html', 'Compile-time Polymorphism']]],
    ['Day 3', 'Robustness', [['module4.html', 'Exception Handling'], ['module5.html', 'Templates & Generics']]],
    ['Day 4', 'Modern C++', [['module6.html', 'STL & Containers'], ['module7.html', 'Advanced C++ Features']]],
    ['Day 5', 'Systems & Internals', [['module8.html', 'Systems Programming']]],
    ['Day 6', 'Qt & Capstone', [['module9.html', 'Qt/QML & Network Programming'], ['module10.html', 'Wrap-up & Evaluation']]]
  ];

  function isCurrent(path) {
    const current = window.location.pathname.replace(/\\/g, '/').split('/').pop() || 'index.html';
    return path.split('/').pop() === current;
  }

  function decorateCurrent(container) {
    container.querySelectorAll('a[href]').forEach((anchor) => {
      const href = anchor.getAttribute('href');
      if (!href || href.startsWith('http') || href.includes('#')) return;
      const normalized = href.replace(/^\.\//, '');
      if (isCurrent(normalized)) {
        anchor.classList.add('is-current');
        anchor.setAttribute('aria-current', 'page');
      }
    });
  }

  function renderTopbar() {
    const topbar = document.querySelector('.topbar-right');
    if (!topbar) return;
    const oldToggle = document.querySelector('.sidebar-toggle');
    if (oldToggle) {
      const newToggle = oldToggle.cloneNode(true);
      oldToggle.replaceWith(newToggle);
    }
    topbar.innerHTML = [
      '<a class="topbar-home" href="' + home + '">Course home</a>',
      '<a href="' + prefix + 'quick-notes.html">Quick notes</a>',
      '<details class="nav-menu"><summary>Study</summary><div class="nav-menu-panel">' +
        link('repo-guide.html', 'Repository guide', '▣') +
        link('module-authoring-context.html', 'Study flow', '↗') +
        link('quick-notes.html', 'Quick notes', '≡') +
      '</div></details>',
      '<details class="nav-menu"><summary>Practice</summary><div class="nav-menu-panel">' +
        link('practice-tests.html', 'Practice MCQ tests', '✎') +
        link('exercise.html', 'Course tracker exercise', '★') +
        link('capstone-work1.html', 'Capstone 1: Smart Office', '★') +
        link('capstone-work2.html', 'Capstone 2: Logistics', '★') +
        link('capstone-work3.html', 'Capstone 3: Fleet command', '★') +
      '</div></details>',
      '<details class="nav-menu"><summary>Explore</summary><div class="nav-menu-panel">' +
        link('explore-more.html', 'Student questions', '?') +
        link('cpp-in-the-wild.html', 'C++ in the Wild', '◎') +
        external('https://github.com/raushan1107/Advanced-cpp-handbook/tree/main/Advanced-cpp-sample-codes', 'Source code', '↗') +
      '</div></details>',
      '<a class="topbar-qt" href="' + prefix + 'qt-qml-learning.html">Learn Qt + QML</a>'
    ].join('');
    decorateCurrent(topbar);
  }

  function renderSidebar() {
    const sidebar = document.querySelector('.sidebar-left');
    if (!sidebar) return;
    const dayMarkup = modules.map((day, index) => {
      const topics = day[2].map((item) => '<li class="nav-topic"><a href="' + prefix + item[0] + '">' + item[1] + '</a></li>').join('');
      return '<div class="nav-day" data-open="true">' +
        '<a class="nav-day-toggle" href="' + home + '#day' + (index + 1) + '" aria-expanded="true">' +
        '<span class="nav-day-icon">◐</span><span class="nav-day-label">' + day[0] + '</span>' +
        '<span class="nav-day-subtitle">' + day[1] + '</span><span class="nav-day-chevron">›</span></a>' +
        '<div class="nav-day-body"><div class="nav-module" data-open="true"><div class="nav-module-label">Available now</div><ul class="nav-topics">' + topics + '</ul></div></div></div>';
    }).join('');

    sidebar.innerHTML = '<div class="sidebar-content">' +
      '<section class="sidebar-section" data-open="true"><button class="sidebar-section-toggle" type="button" aria-expanded="true"><span>Course map</span><span aria-hidden="true">⌄</span></button>' +
      '<nav class="nav-tree" aria-label="Course navigation">' + dayMarkup + '</nav></section>' +
      '<div class="sidebar-divider"></div>' +
      '<section class="sidebar-section" data-open="true"><button class="sidebar-section-toggle" type="button" aria-expanded="true"><span>Learning paths</span><span aria-hidden="true">⌄</span></button>' +
      '<ul class="sidebar-resources">' +
        '<li><a href="' + prefix + 'quick-notes.html">≡ Quick notes</a></li>' +
        '<li><a class="path-highlight" href="' + prefix + 'qt-qml-learning.html">◆ Learn Qt and QML with Raushan</a></li>' +
      '</ul></section>' +
      '<div class="sidebar-divider"></div>' +
      '<section class="sidebar-section" data-open="true"><button class="sidebar-section-toggle" type="button" aria-expanded="true"><span>Resources</span><span aria-hidden="true">⌄</span></button>' +
      '<ul class="sidebar-resources">' +
        '<li><a href="' + prefix + 'practice-tests.html">✎ Practice MCQ tests</a></li>' +
        '<li><a href="' + prefix + 'exercise.html">★ Exercises and capstones</a></li>' +
        '<li><a href="' + prefix + 'repo-guide.html">▣ Repository guide</a></li>' +
        '<li><a href="' + prefix + 'explore-more.html">? Explore more</a></li>' +
        '<li><a href="' + prefix + 'cpp-in-the-wild.html">◎ C++ in the Wild</a></li>' +
        '<li>' + external('https://github.com/raushan1107/Advanced-cpp-handbook/tree/main/Advanced-cpp-sample-codes', 'Source code', '↗') + '</li>' +
      '</ul></section>' +
      '</div>';
    decorateCurrent(sidebar);
  }

  function wireInteractions() {
    const toggle = document.querySelector('.sidebar-toggle');
    const sidebar = document.querySelector('.sidebar-left');
    if (toggle && sidebar && !toggle.dataset.navigationBound) {
      toggle.dataset.navigationBound = 'true';
      toggle.title = 'Show or hide the left navigation';
      toggle.setAttribute('aria-label', 'Show or hide the left navigation');
      const desktop = window.matchMedia('(min-width: 861px)');
      const setCollapsed = (collapsed) => {
        document.body.classList.toggle('sidebar-collapsed', collapsed);
        toggle.setAttribute('aria-expanded', String(!collapsed));
        try {
          window.localStorage.setItem('handbook-sidebar-collapsed', String(collapsed));
        } catch (error) {
        }
      };
      let savedCollapsed = false;
      try {
        savedCollapsed = desktop.matches && window.localStorage.getItem('handbook-sidebar-collapsed') === 'true';
      } catch (error) {
        savedCollapsed = false;
      }
      if (savedCollapsed) {
        document.body.classList.add('sidebar-collapsed');
        toggle.setAttribute('aria-expanded', 'false');
      }
      toggle.addEventListener('click', () => {
        if (desktop.matches) {
          setCollapsed(!document.body.classList.contains('sidebar-collapsed'));
        } else {
          sidebar.classList.toggle('open');
          toggle.setAttribute('aria-expanded', String(sidebar.classList.contains('open')));
        }
      });
      sidebar.querySelectorAll('.nav-day-toggle').forEach((dayToggle) => {
        dayToggle.addEventListener('click', (event) => {
          event.preventDefault();
          const day = dayToggle.closest('.nav-day');
          const open = day.dataset.open === 'true';
          day.dataset.open = String(!open);
          dayToggle.setAttribute('aria-expanded', String(!open));
        });
      });
      sidebar.querySelectorAll('.nav-module-label').forEach((label) => {
        label.setAttribute('role', 'button');
        label.setAttribute('tabindex', '0');
        label.setAttribute('aria-expanded', 'true');
        const module = label.closest('.nav-module');
        const toggleModule = () => {
          const open = module.dataset.open !== 'false';
          module.dataset.open = String(!open);
          label.setAttribute('aria-expanded', String(!open));
        };
        label.addEventListener('click', toggleModule);
        label.addEventListener('keydown', (event) => {
          if (event.key === 'Enter' || event.key === ' ') {
            event.preventDefault();
            toggleModule();
          }
        });
      });
      sidebar.querySelectorAll('.sidebar-section-toggle').forEach((sectionToggle) => {
        sectionToggle.addEventListener('click', () => {
          const section = sectionToggle.closest('.sidebar-section');
          const open = section.dataset.open === 'true';
          section.dataset.open = String(!open);
          sectionToggle.setAttribute('aria-expanded', String(!open));
        });
      });
      sidebar.querySelectorAll('a:not(.nav-day-toggle)').forEach((link) => link.addEventListener('click', () => sidebar.classList.remove('open')));
    }

    document.querySelectorAll('.nav-menu').forEach((menu) => {
      menu.addEventListener('toggle', () => {
        if (!menu.open) return;
        document.querySelectorAll('.nav-menu[open]').forEach((other) => {
          if (other !== menu) other.removeAttribute('open');
        });
      });
    });
  }

  function initializeNavigation() {
    renderTopbar();
    renderSidebar();
    wireInteractions();
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initializeNavigation, { once: true });
  } else {
    initializeNavigation();
  }
}());
