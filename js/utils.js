
const show_element = id => {
    const e = (typeof id === 'string') ? document.getElementById(id) : id;
    e.style.display = '';
};

const hide_element = id => {
    const e = (typeof id === 'string') ? document.getElementById(id) : id;
    e.style.display = 'none';
};

const toggle_element = id => {
    const e = (typeof id === 'string') ? document.getElementById(id) : id;
    if (e.style.display == '') {
        e.style.display = 'none';
    } else {
        e.style.display = '';
    }
};

const toggle_child_element = (el, id) => {
    const e = el.querySelector('#' + id);
    if (e.style.display == '') {
        e.style.display = 'none';
    } else {
        e.style.display = '';
    }
};

const menus = {};
const toggle_menu = (event, contentId) => {
    event.stopPropagation();
    toggle_element(contentId);
    if (!menus[contentId]) {
        menus[contentId] = () => hide_element(contentId);
        window.addEventListener('click', menus[contentId]);
    }
    return false;
};

window.Utils = {
    show_element,
    hide_element,
    toggle_element,
    toggle_child_element,
    toggle_menu
};
