<template>
    <div ref="scoreBarRef" class="chart">
        <!-- <p>{{ fatherDataName }}</p> -->
    </div>
</template>

<script setup lang="ts">
import { onMounted, ref, defineProps, watchEffect } from 'vue';
import * as echarts from 'echarts';
import 'echarts/theme/macarons.js';

const props = defineProps({
    chartData: Object,
});
const scoreBarRef = ref<HTMLDivElement>()
onMounted(() => {
    watchEffect(()=>{
        console.log('props.chartData:',props.chartData);
        let data = props.chartData;
        console.log(data)
        let common = data?.filter((item: any) => { return item.Class == 0 })
        let half = data?.filter((item: any) => { return (item.Class & 1) != 0})
        let score85 = data?.filter((item: any) => { return (item.Class & 2) != 0 })
        // let halfAndScore85 = data?.filter((item: any) => { return item.Class == 3 })

        // 基于准备好的dom，初始化echarts实例
        var myChart = echarts.init(scoreBarRef.value as HTMLDivElement, 'macarons');
        var option = {
            tooltip: {
                trigger: 'item',
                backgroundColor: '#fff',
                axisPointer: {
                    type: 'cross',
                    crossStyle: {
                        color: '#999'
                    }
                },
                formatter: (params: any) => {
                    return `
                            <div style="text-align: left;">
                                <p><strong>姓名:</strong> ${params.data.Name}</p>
                                <p><strong>学号:</strong> ${params.data.ID}</p>
                                <p><strong>分数:</strong> ${params.data.Score}</p>
                            </div>
                        `;
                },
            },
            toolbox: {
                feature: {
                    dataView: { show: true, readOnly: false },
                    magicType: { show: true, type: ['scatter'] },
                    restore: { show: true },
                    saveAsImage: { show: true }
                }
            },
            dataset: [{
                source: common,
                dimensions: ["Index", "Score"]
            },
            {
                source: half,
                dimensions: ["Index", "Score"]
            },
            {
                source: score85,
                dimensions: ["Index", "Score"]
            },
            // {
            //     source: halfAndScore85,
            //     dimensions: ["Index", "Score"]
            // }
            ],
            xAxis: {
                type: 'value',
                name: "排名",
                large: true,
                axisPointer: {
                    type: 'line',
                    snap: true
                },
                axisLabel: {
                    show: true,
                    interval: 'auto',
                }
            },
            yAxis: {
                type: 'value',
                name: "分数"
            },
            series: [{
                name: '分数',
                type: 'scatter',
                datasetIndex: 0,
                symbolSize: 10,
                selectedMode: "single",
            },
            {
                name: '50%',
                type: 'scatter',
                datasetIndex: 1,
                symbolSize: 15,
                selectedMode: "single",
            },
            {
                name: '85分',
                type: 'scatter',
                datasetIndex: 2,
                symbolSize: 15,
                selectedMode: "single",
            },
            // {
            //     name: '50%且85分',
            //     type: 'scatter',
            //     datasetIndex: 3,
            //     symbolSize: 15,
            //     selectedMode: "single",
            // }
            ],
            grid: {
                top: 100,
            },
            legend: {
            }
        };

        // 绘制图表
        option && myChart.setOption(option);
        myChart.resize()
        window.addEventListener('resize', () => {
            myChart.resize()
        })
    })
})
</script>
<style scoped>
.chart {
    width: 100%;
    height: 500px;
}
</style>