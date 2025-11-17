import os
import random
import re
import sys

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.
    """
    n = len(corpus)
    prob_distribution = dict()
    links = corpus[page]

    if links:
        for p in corpus:
            prob_distribution[p] = (1 - damping_factor) / n
        for link in links:
            prob_distribution[link] += damping_factor / len(links)
    else:
        # Treat as if it has links to all pages
        for p in corpus:
            prob_distribution[p] = 1 / n

    return prob_distribution


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.
    """
    pagerank = {page: 0 for page in corpus}
    pages = list(corpus.keys())
    current_page = random.choice(pages)

    for _ in range(n):
        pagerank[current_page] += 1
        distribution = transition_model(corpus, current_page, damping_factor)
        current_page = random.choices(
            population=list(distribution.keys()),
            weights=list(distribution.values()),
            k=1
        )[0]

    # Normalize values to sum to 1
    for page in pagerank:
        pagerank[page] /= n

    return pagerank


def iterate_pagerank(corpus, damping_factor, threshold=0.001):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.
    """
    num_pages = len(corpus)
    pagerank = {page: 1 / num_pages for page in corpus}

    converged = False
    while not converged:
        new_pagerank = dict()
        for page in corpus:
            total = 0
            for potential_linker in corpus:
                if page in corpus[potential_linker]:
                    total += pagerank[potential_linker] / len(corpus[potential_linker])
                if not corpus[potential_linker]:  # Page with no links
                    total += pagerank[potential_linker] / num_pages
            new_rank = (1 - damping_factor) / num_pages + damping_factor * total
            new_pagerank[page] = new_rank

        # Check for convergence
        converged = all(abs(new_pagerank[p] - pagerank[p]) < threshold for p in pagerank)
        pagerank = new_pagerank

    # Normalize values to sum to 1
    total_rank = sum(pagerank.values())
    for page in pagerank:
        pagerank[page] /= total_rank

    return pagerank


if __name__ == "__main__":
    main()
