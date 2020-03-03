<template>
  <div :style="style.overlay">
    <div :style="{flex:1}" />
    <div :style="{display:'flex', flexDirection: 'column'}">
      <div :style="{flex:1}" />
      <div :style="[style.modalContainer, {width}]">
        <div :style="style.modalHeader">
          <div style="flex:1; padding: 4px">
            <slot name="header">
              Header
            </slot>
          </div>
          <div>
            <a
              href="javascript:"
              style="width:12px; padding: 5px 8px; position:absolute; margin-left: -25px"
              @click="$emit('dismiss')"
            >
              <font-awesome-icon icon="times" />
            </a>
          </div>
        </div>
        <tw-loading v-if="loading" />

        <div :style="style.modalBody">
          <slot />
        </div>
        <div :style="style.modalFooter">
          <div style="flex:1; padding: 4px">
            <slot name="footer" />
          </div>
        </div>
      </div>
      <div :style="{flex:1}" />
    </div>
    <div :style="{flex:1}" />
  </div>
</template>

<script>
export default {
  props: {
    width: {
      type: String,
      default: undefined,
    },
    loading: {
      type: Boolean,
      default: false,
    },
  },
  data: () => ({
    style: {
      modalContainer: {
        boxShadow: '0 8px 24px 0 rgba(50, 51, 52, 0.5)',
        backgroundColor: 'white',
        borderRadius: '4px',
        display: 'flex',
        flexDirection: 'column',
        minWidth: '400px',
      },
      modalHeader: {
        display: 'flex',
        padding: '4px',
        borderBottom: '1px solid rgba(0,0,0,0.1)',
        minHeight: '30px',
      },
      modalBody: {
        minHeight: '100px',
        maxHeight: `${window.innerHeight - 200}px`,
        overflowY: 'auto',
        overflowX: 'auto',
        flex: 1,
        // backgroundColor: "#f5f7fb"
      },
      modalFooter: {},
      overlay: {
        display: 'flex',
        width: '100%',
        height: '100%',
        position: 'fixed',
        backgroundColor: 'rgba(0,0,0,0.35)',
        top: 0,
        left: 0,
        'z-index': 9999,
      },
    },
  }),
};
</script>
