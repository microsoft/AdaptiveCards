<template>
    <v-container>
        <v-row>
            <v-col>
                <v-stage ref="stage" :config="stageSize">
                    <v-layer ref="layer">
                        <v-image :config="{ image: image }" />
                    </v-layer>
                </v-stage>
            </v-col>
            <v-col>
                <p>Second col</p>
            </v-col>
        </v-row>
    </v-container>
</template>

<script>
const width = window.innerWidth
const height = window.innerHeight
export default {
    name: 'ImageCanvas',
    props: {
        image_url: {}
    },
    data() {
        return {
            image: null,
            stageSize: {
                width: 0,
                height: 0
            }
        }
    },
    beforeMount() {
        const image = new window.Image()
        // image.src = 'https://konvajs.org/assets/yoda.jpg'
        image.src = this.image_url
        image.onload = () => {
            this.image = image
            //console.log(image.width)
            this.stageSize.width = image.width
            this.stageSize.height = image.height
        }
    }
    // created() {
    //     const image = new window.Image()
    //     image.src = 'https://konvajs.org/assets/yoda.jpg'
    //     image.onload = () => {
    //         this.image = image
    //     }
    // }
}
</script>
