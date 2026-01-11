(function () {
    'use strict';

    // Check if user is authenticated (set by layout)
    const isAuthenticated = window.isAuthenticated || false;

    // Event delegation for vote buttons
    document.addEventListener('click', async function (e) {
        const btn = e.target.closest('.vote-btn');
        if (!btn) return;

        // Prevent the click from propagating to parent links (stretched-link)
        e.preventDefault();
        e.stopPropagation();

        // Check authentication
        if (!isAuthenticated) {
            window.location.href = '/Account/Login?ReturnUrl=' + encodeURIComponent(window.location.pathname);
            return;
        }

        const bookmarkId = parseInt(btn.dataset.bookmarkId, 10);
        if (!bookmarkId) return;

        // Disable button during request
        btn.disabled = true;

        try {
            const response = await csrf.fetch(API.VOTES.TOGGLE, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ bookmarkId: bookmarkId })
            });

            const data = await response.json();

            if (response.ok && data.success) {
                // Update UI
                updateVoteButton(btn, data.isLiked, data.voteCount);
            } else {
                showToast(data.message || 'Failed to update vote', 'danger');
            }
        } catch (error) {
            console.error('Vote error:', error);
            showToast('An error occurred. Please try again.', 'danger');
        } finally {
            btn.disabled = false;
        }
    });

    function updateVoteButton(btn, isLiked, voteCount) {
        const previousCount = parseInt(btn.querySelector('.vote-count')?.textContent || '0', 10);

        // Update data attribute
        btn.dataset.liked = isLiked.toString();

        // Update icon
        const icon = btn.querySelector('i');
        if (icon) {
            if (isLiked) {
                icon.classList.remove('bi-heart');
                icon.classList.add('bi-heart-fill');

                // Trigger burst effect on like
                btn.classList.add('vote-burst');
                setTimeout(() => btn.classList.remove('vote-burst'), 600);
            } else {
                icon.classList.remove('bi-heart-fill');
                icon.classList.add('bi-heart');
            }

            // Add heart pop animation
            icon.classList.add('vote-animate');
            setTimeout(() => icon.classList.remove('vote-animate'), 500);
        }

        // Update count with slide animation
        const countSpan = btn.querySelector('.vote-count');
        if (countSpan) {
            // Determine animation direction based on count change
            const slideClass = voteCount > previousCount ? 'vote-count-up' : 'vote-count-down';

            countSpan.classList.add(slideClass);
            countSpan.textContent = voteCount;

            setTimeout(() => countSpan.classList.remove(slideClass), 250);
        }
    }

    // showToast is provided by shared/toast.js
})();
