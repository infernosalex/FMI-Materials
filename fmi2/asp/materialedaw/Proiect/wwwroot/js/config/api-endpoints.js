/**
 * API Endpoints Configuration
 * Centralized location for all API route definitions
 */

const API = {
    // Categories endpoints
    CATEGORIES: {
        CREATE_QUICK: '/Categories/CreateQuick',
        GET_USER_CATEGORIES: '/Categories/GetUserCategories',
        TOGGLE_BOOKMARK: '/Categories/ToggleBookmark'
    },

    // Tags endpoints
    TAGS: {
        CREATE_QUICK: '/Tags/CreateQuick',
        SEARCH: '/Tags/Search'
    },

    // Bookmarks endpoints
    BOOKMARKS: {
        SUGGEST_TAGS: '/Bookmarks/SuggestTags'
    },

    // Comments endpoints
    COMMENTS: {
        CREATE: '/Comments/Create',
        EDIT: '/Comments/Edit',
        DELETE: '/Comments/Delete'
    },

    // Votes endpoints
    VOTES: {
        TOGGLE: '/Votes/Toggle'
    },

    // Home feed endpoints
    HOME: {
        FEED: '/Home/Feed'
    },

    // Search endpoints
    SEARCH: {
        RESULTS: '/Search/Results'
    },

    // Antiforgery endpoint
    ANTIFORGERY: '/antiforgery/token'
};

// Export for use in other modules
window.API = API;
