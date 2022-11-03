const minMax = (tables: number[][]) => {
  let minTab: number[] = [];
  let maxTab: number[] = [];

  tables.map((table) => {
    const min = Math.min(...table);
    const max = Math.max(...table);
    minTab.push(min);
    maxTab.push(max);
  });
  return { minTab, maxTab };
};

export default minMax;

export const minMaxGlobal = (tables: number[][]) => {
  let minTab: number[] = [];
  let maxTab: number[] = [];

  tables.map((table) => {
    const min = Math.min(...table);
    const max = Math.max(...table);
    minTab.push(min);
    maxTab.push(max);
  });

  const min = Math.min(...minTab);
  const max = Math.max(...minTab);

  return { min, max };
};
