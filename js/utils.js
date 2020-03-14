
const hide_element = id => {
    const e = document.getElementById(id);
    e.style.display = 'none';
};

const toggle_element = id => {
    const e = document.getElementById(id);
    if (e.style.display == 'block') {
        e.style.display = 'none';
    } else {
        e.style.display = 'block';
    }
};

const toggle_child_element = (el, id) => {
    const e = el.querySelector('#' + id);
    if (e.style.display == 'block') {
        e.style.display = 'none';
    } else {
        e.style.display = 'block';
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
    toggle_element,
    toggle_child_element,
    toggle_menu
};
