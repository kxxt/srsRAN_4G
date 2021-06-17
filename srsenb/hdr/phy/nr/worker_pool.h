/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2021 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#ifndef SRSENB_NR_WORKER_POOL_H
#define SRSENB_NR_WORKER_POOL_H

#include "sf_worker.h"
#include "srsenb/hdr/phy/phy_interfaces.h"
#include "srsran/common/thread_pool.h"

namespace srsenb {
namespace nr {

class worker_pool
{
  srsran::thread_pool                      pool;
  std::vector<std::unique_ptr<sf_worker> > workers;
  phy_nr_state                             phy_state;

public:
  sf_worker* operator[](std::size_t pos) { return workers.at(pos).get(); }

  worker_pool(uint32_t max_workers);
  bool       init(const phy_cell_cfg_list_nr_t& cell_list,
                  const phy_args_t&             args,
                  srsran::phy_common_interface& common,
                  srslog::sink&                 log_sink,
                  int                           prio);
  sf_worker* wait_worker(uint32_t tti);
  sf_worker* wait_worker_id(uint32_t id);
  void       start_worker(sf_worker* w);
  void       stop();
};

} // namespace nr
} // namespace srsenb

#endif // SRSENB_NR_WORKER_POOL_H
