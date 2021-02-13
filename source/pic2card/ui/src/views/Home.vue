<template>
    <div>
        <Pic2Card
            v-for="(base64_image, index) in base64_images"
            :key="index"
            v-bind:base64_image="base64_image"
        />
    </div>
</template>

<script>
import Pic2Card from '@/components/Pic2Card.vue'
import getTemplateImages from '@/services/ImageApi.js'

export default {
    name: 'Home',
    components: {
        Pic2Card
    },

    data() {
        return {
            base64_images: []
        }
    },
    mounted() {
        // console.log('working..')
        getTemplateImages.getTemplateImages().then(response => {
            let cards = response.data['templates']
            // this.base64_images = [cards[0], cards[1], cards[2]]
            this.base64_images = cards
            // console.log(this.base64_images)
        })
    }
}
</script>

<style scoped></style>
