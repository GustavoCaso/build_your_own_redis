#include "hashtable.hpp"
#include <assert.h>

// n must be power of 2
static void h_init(HTab *htab, size_t n)
{
  assert(n > 0 && ((n - 1) & n) == 0);
  htab->tab = (HNode **)calloc(sizeof(HNode *), n);
  htab->mask = n - 1;
  htab->size = 0;
}

// hashtable insertion
static void h_insert(HTab *htab, HNode *node)
{
  size_t pos = node->hcode & htab->mask;
  HNode *next = htab->tab[pos];
  node->next = next;
  htab->tab[pos] = node;
  htab->size++;
}

// hashtable look up subroutine
// Pay attention to the return value. It return the address of
//  the parent pointer that owns the target node,
// which can be used to delete the target node.

static HNode **h_lookup(HTab *htab, HNode *key, bool (*cmp)(HNode *, HNode *))
{
  if (!htab->tab)
  {
    return NULL;
  }

  size_t pos = key->hcode & htab->mask;
  HNode **from = &htab->tab[pos];
  while (*from)
  {
    if (cmp(*from, key))
    {
      return from;
    }
    from = &(*from)->next;
  }

  return NULL;
}

static HNode *h_detach(HTab *htab, HNode **from)
{
  HNode *node = *from;
  *from = (*from)->next;
  htab->size--;
  return node;
}

const size_t k_resizing_work = 128;

static void hm_help_resizing(HMap *hmap)
{
  if (hmap->ht2.tab == NULL)
  {
    return;
  }

  size_t nwork = 0;
  while (nwork < k_resizing_work && hmap->ht2.size > 0)
  {
    // scan for nodes from ht2 and move them to ht1
    HNode **from = &hmap->ht2.tab[hmap->resizing_pos];
    if (!*from)
    {
      hmap->resizing_pos++;
      continue;
    }

    h_insert(&hmap->ht1, h_detach(&hmap->ht2, from));
    nwork++;
  }

  if (hmap->ht2.size == 0)
  {
    // done
    free(hmap->ht2.tab);
    hmap->ht2 = HTab{};
  }
}

HNode *hm_lookup(HMap *hmap, HNode *key, bool (*cmp)(HNode *, HNode *))
{
  hm_help_resizing(hmap);
  HNode **from = h_lookup(&hmap->ht1, key, cmp);
  if (!from)
  {
    from = h_lookup(&hmap->ht2, key, cmp);
  }
  return from ? *from : NULL;
}

static void hm_start_resizing(HMap *hmap)
{
  assert(hmap->ht2.tab == NULL);
  // create bigger hashtable and swap
  hmap->ht2 = hmap->ht1;
  h_init(&hmap->ht1, (hmap->ht1.mask + 1) * 2);
  hmap->resizing_pos = 0;
}

const size_t k_max_load_factor = 8;

void hm_insert(HMap *hmap, HNode *node)
{
  if (!hmap->ht1.tab)
  {
    h_init(&hmap->ht1, 4);
  }
  h_insert(&hmap->ht1, node);

  if (!hmap->ht2.tab)
  {
    // check wheter we need to resize
    size_t load_factor = hmap->ht1.size / (hmap->ht1.mask + 1);
    if (load_factor >= k_max_load_factor)
    {
      hm_start_resizing(hmap);
    }
  }
  hm_help_resizing(hmap);
}

HNode *hm_pop(HMap *hmap, HNode *key, bool (*cmp)(HNode *, HNode *))
{
  hm_help_resizing(hmap);
  HNode **from = h_lookup(&hmap->ht1, key, cmp);
  if (from)
  {
    return h_detach(&hmap->ht1, from);
  }
  from = h_lookup(&hmap->ht2, key, cmp);
  if (from)
  {
    return h_detach(&hmap->ht2, from);
  }
  return NULL;
}
