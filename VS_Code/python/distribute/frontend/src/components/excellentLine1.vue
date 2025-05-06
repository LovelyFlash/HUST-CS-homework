<template>
    <div ref="excellentLineRef" class="chart" id="excLine">

    </div>
</template>

<script setup lang="ts">
import { onMounted, ref } from 'vue';
import * as echarts from 'echarts';
import 'echarts/theme/macarons.js';
import { fetchExcellentLineData } from '../api/index';
import { el } from 'element-plus/es/locale';

onMounted(() => {
    fetchExcellentLineData().then(res => {
        console.log(res.data);
        let data = res.data.data;
        console.log(data);
        
        let year = [];
        let series = []
        for (var key in data) {
            let year_name = key + '级'
            year.push(year_name)
            var dict = {
                name: year_name,
                type: 'bar',
                smooth: true,
                tooltip: {
                    valueFormatter: function (value: string) {
                        return value + ' %';
                    }
                },
                data: [] as any,
                itemStyle: {
                        normal: {
                            label: {
                                show: true,
                                position: 'top',
                                textStyle: {
                                    color: 'black',
                                    fontSize: 12,
                                },
                                formatter: function(realData:any) {
                                    return realData.value+'%'
                                }
                            }
                        }
                    }
            };
            let d = data[key]
            let arr = new Array(3).fill(0);
            for(var k in d){
                if(k == 'grade1'){
                    arr[0]=d[k].excellentRate
                }
                else if(k == 'grade2'){
                    arr[1]=d[k].excellentRate
                }
                else if(k == 'grade3'){
                    arr[2]=d[k].excellentRate
                }
            }
            dict.data = arr;
            series.push(dict)
        }
        var app: any = {};
        type EChartsOption = echarts.EChartsOption;

        var chartDom = document.getElementById('excLine')!;
        var myChart = echarts.init(chartDom);
        var option: EChartsOption;

        const posList = [
        'left',
        'right',
        'top',
        'bottom',
        'inside',
        'insideTop',
        'insideLeft',
        'insideRight',
        'insideBottom',
        'insideTopLeft',
        'insideTopRight',
        'insideBottomLeft',
        'insideBottomRight'
        ] as const;

        app.configParameters = {
        rotate: {
            min: -90,
            max: 90
        },
        align: {
            options: {
            left: 'left',
            center: 'center',
            right: 'right'
            }
        },
        verticalAlign: {
            options: {
            top: 'top',
            middle: 'middle',
            bottom: 'bottom'
            }
        },
        position: {
            options: posList.reduce(function (map, pos) {
            map[pos] = pos;
            return map;
            }, {} as Record<string, string>)
        },
        distance: {
            min: 0,
            max: 100
        }
        };

        app.config = {
        rotate: 0,
        align: 'center',
        verticalAlign: 'middle',
        position: 'top',
        distance: 15,
        onChange: function () {
            const labelOption: BarLabelOption = {
            rotate: app.config.rotate as BarLabelOption['rotate'],
            align: app.config.align as BarLabelOption['align'],
            verticalAlign: app.config
                .verticalAlign as BarLabelOption['verticalAlign'],
            position: app.config.position as BarLabelOption['position'],
            distance: app.config.distance as BarLabelOption['distance']
            };
            myChart.setOption<echarts.EChartsOption>({
            series: [
                {
                label: labelOption
                },
                {
                label: labelOption
                },
                {
                label: labelOption
                },
                {
                label: labelOption
                }
            ]
            });
        }
        };

        type BarLabelOption = NonNullable<echarts.BarSeriesOption['label']>;

        const labelOption: BarLabelOption = {
            show: true,
            position: app.config.position as BarLabelOption['position'],
            distance: app.config.distance as BarLabelOption['distance'],
            align: app.config.align as BarLabelOption['align'],
            verticalAlign: app.config.verticalAlign as BarLabelOption['verticalAlign'],
            rotate: app.config.rotate as BarLabelOption['rotate'],
            formatter: '{c}%  {name|{a}}',
            fontSize: 16,
            rich: {
                name: {}
            }
        };
        var infos = res.data.data;
        console.log(infos)
        let legends = [];
        let xDatas = [];
        let tempIdx = 0;
        let tempKey = '';
        let tempArray = [];
        let seriesItem = {};
        let seriesData = [];
        for(var key in infos) {
            legends.push(key + '级');
            tempArray = [NaN, NaN, NaN];
            for(var k in infos[key]) {
                if (k.slice(5)=='1') {
                    tempIdx = 0;
                    tempKey = '大一';
                    tempArray[0] = infos[key][k].excellentRate
                } else if (k.slice(5)=='2') {
                    tempIdx = 1;
                    tempKey = '大二';
                    tempArray[1] = infos[key][k].excellentRate
                } else if (k.slice(5)=='3') {
                    tempIdx = 2;
                    tempKey = '大三';
                    tempArray[2] = infos[key][k].excellentRate
                }
                if (!xDatas[tempIdx]) { // 如果x轴标签未补充完整
                    xDatas[tempIdx] = tempKey;
                }
            }
            seriesItem = {
                name: key + '级',
                type: 'line',
                barGap: 0,
                label: labelOption,
                emphasis: {
                    focus: 'series'
                },
                data: tempArray
            }
            seriesData.push(seriesItem);
        }
        console.log(legends);//年级数组
        console.log(xDatas);//x轴
        console.log(seriesData);//series的数据
         
        option = {
            tooltip: {
                trigger: 'axis',
                axisPointer: {
                type: 'shadow'
                }
            },
            grid: {
                top: 100,
            },
            legend: {
                show: true,
                data: legends,
                left: 'left'
            },
            toolbox: {
                show: true,
                orient: 'horizontal',
                left: 'right',
                top: 'top',
                iconStyle: {
                    borderColor: '#2EC7C9',
                },
                feature: {
                mark: { show: true },
                dataView: { show: true, readOnly: false },
                magicType: { show: true, type: ['line', 'bar'] },
                restore: { show: true },
                saveAsImage: { show: true }
                }
            },
            xAxis: [
                {
                    type: 'category',
                    name: '年级',
                    nameTextStyle: {
                        fontSize: '16'
                    },
                    axisTick: { show: false },
                    data: xDatas,
                    axisLine: {
                        lineStyle: {
                            color: 'rgb(59,165,217)'
                        }
                    }
                },
            ],
            yAxis: [
                {
                    type: 'value',
                    name: '优良学风班比例',
                    nameTextStyle: {
                        fontSize: '16'
                    },
                    axisLabel: {
                        formatter: '{value} %',
                    },
                    axisLine: {
                        lineStyle: {
                            color: 'rgb(59,165,217)'
                        }
                    }
                }
            ],
            series: seriesData
        };
        // 绘制图表
        option && myChart.setOption(option);
        myChart.resize();
    })
})
</script>
<style scoped>
.chart {
    width: 100%;
    height: 500px;
}
</style>